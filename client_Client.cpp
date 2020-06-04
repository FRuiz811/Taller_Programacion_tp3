#include "client_Client.h"
#include <string>
#include <iostream>
#include <sys/socket.h>
#include <syslog.h>
#include <arpa/inet.h>
#include <vector>

#define LOSER "Perdiste"
#define WINNER "Ganaste"
#define INVALID_COMMAND "Error: comando inválido. "\
						 "Escriba AYUDA para obtener ayuda"
#define UNKNOW_ERROR "Unknow Error"
#define LOG_MSG	"Invalid command entered by client.\n"

Client::Client(const char* host, const char* port) : socket(), protocol(), 
	keep_talking(true) {
	this->socket.connect(host, port);
}

void Client::send_message(const std::string& command) {
	std::vector<char> message;
	message = this->protocol.encode_command(command);
	this->socket.send(message.data(), message.size());
	return;
}

std::string Client::recieve_message() {
	uint8_t length[4];	
	this->socket.recieve(&length, 4);
	uint32_t* temp32 = (uint32_t*) length;
	uint32_t length_message = ntohl(*temp32);

	std::vector<char> data(length_message+1, 0);
	std::string decoded;
	char *buf = data.data();
	this->socket.recieve(buf, length_message);
	decoded = buf + '\0';
	return decoded;
}

void Client::run() {
	std::string command;
	while (keep_talking) {
		try{
			std::getline(std::cin, command);
			if(command.empty())
				break;
			send_message(command);
			std::string response = recieve_message();
			std::cout << response << std::endl;
			if (response == LOSER || response == WINNER)
				this->keep_talking = false;			
		} catch (const std::exception& e) {
			std::cout <<  INVALID_COMMAND << std::endl;
 			syslog(LOG_CRIT, LOG_MSG);
		} catch (...) {
			syslog(LOG_CRIT, UNKNOW_ERROR);
		}
	}
	return;
}

Client::~Client() {
	this->socket.shutdown(SHUT_RDWR);
}
