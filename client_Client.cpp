#include "client_Client.h"
#include <string>
#include <iostream>
#include <sys/socket.h>
#include <syslog.h>

Client::Client(const char* host, const char* port) : socket(), protocol(), 
	keep_talking(true) {
	this->socket.connect(host, port);
}

void Client::send_message(const std::string& command) {
	std::vector<char> message;

	message = this->protocol.encode_command(command);
	size_t  size = message.size();
	this->socket.send(message.data(), size);

	return;
}

void Client::run() {
	std::string command;
	while (keep_talking) {
		try{
			std::getline(std::cin, command);
			send_message(command);
			//Recive respuesta del servidor
			//this->protocol.decode(command); 
			//std::cout << command;
		} catch (const std::exception& e) {
			std::cout << "Error: comando inválido." << " " <<
 										"Escriba AYUDA para obtener ayuda\n";
 			syslog(LOG_CRIT, "Invalid command entered by client.\n");
		} catch (...) {
			syslog(LOG_CRIT, "Unknow Error");
		}
	}
	return;
}

Client::~Client() {
	this->socket.shutdown(SHUT_RDWR);
}