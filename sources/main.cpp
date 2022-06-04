#include "Server.hpp"

int main(int argc, const char *argv[]) {
	if (argc < 3) {
		std::cout << "Usage: ./ircserv <port> <password>";
		exit(EXIT_FAILURE);
	}

	int port = atoi(argv[1]);
	if (port < 1024 || port > 49151) {
		std::cout << "Incorrect port! Should be in range of 1024 to 49152" << std::endl;
		exit(EXIT_FAILURE);
	}

	Server	server(port, argv[2]);

	server.
}