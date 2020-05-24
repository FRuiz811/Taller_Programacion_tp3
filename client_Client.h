#ifndef CLIENT_H
#define CLIENT_H

#include "common_Socket.h"
#include "common_Protocol.h"
#include <cstdint>
#include <string>
#include <atomic>

class Client {
private:
	Socket socket;
	Protocol protocol;
	std::atomic<bool> keep_talking;

	void send_message(const std::string& command);
	std::string recieve_message();
public:
	explicit Client(const char* host, const char* port);

	void run();

	~Client();

	Client(Client&& other) = delete;
	Client& operator=(Client&& other) = delete;
	Client(const Client& other) = delete;
	Client& operator=(const Client& other) = delete;
};

#endif
