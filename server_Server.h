#ifndef SERVER_H
#define SERVER_H

#include "server_SecretNumbers.h"
#include "server_GamesAcceptor.h"
#include <string>

class Server {
private:
	SecretNumbers numbers;
	GamesAcceptor gamesAcceptor;
public:
	explicit Server(const char* port, const std::string& fileNumbers);

	void run();

	~Server();
};

#endif
