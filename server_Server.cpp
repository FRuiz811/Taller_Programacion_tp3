#include "server_Server.h"
#include <iostream>


Server::Server(const char* port, const std::string& fileNumbers) : 
	numbers(fileNumbers) {
}

void Server::run() {
	std::string input;
	while (input != "q") {
		std::cin >> input;
	}
}

Server::~Server() {}