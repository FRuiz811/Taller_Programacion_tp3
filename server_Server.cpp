#include "server_Server.h"
#include <iostream>
#include <string>

Server::Server(const char* port, const std::string& fileNumbers) : 
	numbers(fileNumbers), board() , gamesAcceptor(port, numbers,board) {
		this->gamesAcceptor.start();
}

void Server::run() {
	std::string input;
	while (input != "q") {
		std::cin >> input;
	}
	this->gamesAcceptor.stop();
	this->board.show_results();
}

Server::~Server() {
	this->gamesAcceptor.join();
}
