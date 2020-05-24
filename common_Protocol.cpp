#include "common_Protocol.h"
#include <string>
#include <arpa/inet.h>

Protocol::Protocol() : message() {}

std::vector<char> Protocol::encode_command(const std::string& command) {
	this->message.clear();
	if (command == "AYUDA") {
		this->message.push_back('h');
	} else if (command == "RENDIRSE") {
		this->message.push_back('s');
	} else {
		this->message.push_back('n');
		unsigned short number = std::stoi(command);
		unsigned short big_endian = htons(number);
		char *c = (char*) &big_endian;
		this->message.push_back(*c);
		this->message.push_back(*(c+1));
	}
	return this->message;
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
	return this->message;
}

Protocol::~Protocol() {}