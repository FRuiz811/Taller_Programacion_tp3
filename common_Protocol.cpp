#include "common_Protocol.h"
#include <string>
#include <arpa/inet.h>
#include <utility>
#include <stdexcept>

#define HELP "AYUDA"
#define SURRENDER "RENDIRSE"
#define COMMAND_HELP 'h'
#define COMMAND_SURRENDER 's'
#define COMMAND_PLAY 'n'
#define INVALID_RANGE "No está en el rango permitido"
#define MAX_USHORT 65535

Protocol::Protocol() : message() {}

std::vector<char> Protocol::encode_command(const std::string& command) {
	this->message.clear();
	if (command == HELP) {
		this->message.push_back(COMMAND_HELP);
	} else if (command == SURRENDER) {
		this->message.push_back(COMMAND_SURRENDER);
	} else {
		int number = std::stoi(command);
		if (number < 0 || number > MAX_USHORT)
			throw std::out_of_range(INVALID_RANGE);
		this->message.push_back(COMMAND_PLAY);
		unsigned short big_endian = htons(number);
		char *c = (char*) &big_endian;
		this->message.push_back(*c);
		this->message.push_back(*(c+1));
	}
	return std::move(this->message);
}

std::vector<char> Protocol::encode_string(const std::string& messageToEncode) {
	this->message.clear();
	size_t size = messageToEncode.size();
	unsigned int big_endian = htonl(size);
	char *c = (char*) &big_endian;
	for (size_t i = 0; i < 4; i++) {
		this->message.push_back(*(c+i));
	}
	for (size_t i = 0; i < messageToEncode.size(); i++) {
		this->message.push_back(messageToEncode[i]);
	}
	return std::move(this->message);
}

Protocol::~Protocol() {}
