#ifndef SERVER_H
#define SERVER_H

#include "server_SecretNumbers.h"

class Server {
private:
	SecretNumbers numbers;
public:
	explicit Server(const char* port, const std::string& fileNumbers);

	void run();

	~Server();

};

#endif
