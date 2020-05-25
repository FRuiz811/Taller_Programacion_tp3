#include "server_Server.h"
#include <iostream>
#include <string>

Server::Server(const char* port, const std::string& fileNumbers) : 
	numbers(fileNumbers) , gamesAcceptor(port, numbers) {
		this->gamesAcceptor.start();
}

void Server::run() {
	std::string input;
	while (input != "q") {
		std::cin >> input;
	}
}

Server::~Server() {
	this->gamesAcceptor.stop();
	this->gamesAcceptor.join();
}
