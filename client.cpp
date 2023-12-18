#include <zmq.hpp>
#include <string>
#include <iostream>

int main() {
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REQ);

    std::cout << "Connecting to server..." << std::endl;
    socket.connect("tcp://localhost:5555");

    while (true) {
        std::string guess;
        std::cout << "Enter your guess (or 'exit' to quit): ";
        std::cin >> guess;

        zmq::message_t request(guess.size());
        memcpy(request.data(), guess.data(), guess.size());
        socket.send(request);

        // Получаем ответ
        zmq::message_t reply;
        socket.recv(&reply);
        std::string response = std::string(static_cast<char*>(reply.data()), reply.size());
        std::cout << response << std::endl;

        if (response == "Congratulations! You have guessed the word." || response == "You have exited the game.") {
            break;
        }
    }

    return 0;
}