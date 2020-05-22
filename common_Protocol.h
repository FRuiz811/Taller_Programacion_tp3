#ifndef COMMON_PROTOCOL_H
#define COMMON_PROTOCOL_H

#include <string>
#include <vector>

class Protocol {
private:
	std::vector<char> message;
public:
	Protocol();

	std::vector<char> encode_command(const std::string& command);
	//std::vector<char> encode_string(const std::string& message);
	std::vector<char> decode(const std::string& message);
	~Protocol();

	Protocol(const Protocol& other) = delete;
	Protocol& operator=(const Protocol& other) = delete;
};

#endif
