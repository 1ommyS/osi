#include <zmq.hpp>
#include <string>
#include <iostream>
#include <thread>
#include <map>
#include <vector>

// Функция для подсчета быков и коров
std::pair<int, int> count_bulls_cows(const std::string &guess, const std::string &word)
{
    int bulls = 0;
    int cows = 0;
    for (int i = 0; i < guess.size(); ++i)
    {
        if (guess[i] == word[i])
        {
            ++bulls;
        }
        else if (word.find(guess[i]) != std::string::npos)
        {
            ++cows;
        }
    }
    return {bulls, cows};
}

void handle_client(zmq::context_t &context, const std::string &word)
{
    zmq::socket_t socket(context, ZMQ_REP);
    socket.connect("inproc://workers");

    while (true)
    {
        zmq::message_t request;
        socket.recv(&request);
        std::string guess = std::string(static_cast<char *>(request.data()), request.size());

        if (guess == "exit")
        {
            std::string response = "You have exited the game.";
            zmq::message_t reply(response.size());
            memcpy(reply.data(), response.data(), response.size());
            socket.send(reply);
            break;
        }

        auto [bulls, cows] = count_bulls_cows(guess, word);
        std::string response;
        if (bulls == word.size())
        {
            response = "Congratulations! You have guessed the word.";
        }
        else
        {
            response = "Bulls: " + std::to_string(bulls) + ", Cows: " + std::to_string(cows);
        }

        zmq::message_t reply(response.size());
        memcpy(reply.data(), response.data(), response.size());
        socket.send(reply);
    }
}

int main()
{
    zmq::context_t context(1);
    zmq::socket_t clients(context, ZMQ_ROUTER);
    clients.bind("tcp://*:5555");

    zmq::socket_t workers(context, ZMQ_DEALER);
    workers.bind("inproc://workers");

    const std::string word = "hello"; // Загаданное слово

    int num_players;
    std::cout << "Введите количество игроков: ";
    std::cin >> num_players;

    std::vector<std::thread> threads;
    for (int i = 0; i < num_players; ++i)
    {
        threads.emplace_back(handle_client, std::ref(context), word);
    }

    zmq::proxy(static_cast<void *>(clients), static_cast<void *>(workers), nullptr);

    for (auto &thread : threads)
    {
        thread.join();
    }

    return 0;
}