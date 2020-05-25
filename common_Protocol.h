#ifndef COMMON_PROTOCOL_H
#define COMMON_PROTOCOL_H

#include <string>
#include <vector>

//Protocol es la clase encargada de encodear el envio de los mensajes
//que se utilizaran para la comunicación entre Server y Client.
class Protocol {
private:
	std::vector<char> message;
public:
	Protocol();

	std::vector<char> encode_command(const std::string& command);
	std::vector<char> encode_string(const std::string& messageToEncode);
	~Protocol();

	Protocol(const Protocol& other) = delete;
	Protocol& operator=(const Protocol& other) = delete;
};

#endif
