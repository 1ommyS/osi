all: server client

server:
	g++ server.cpp -lzmq -pthread  -o server  --std=c++17 -L /usr/local/include 

client:
	g++ client.cpp -lzmq -pthread -o client --std=c++17 -L /usr/local/include

clean:
	rm -rf server client