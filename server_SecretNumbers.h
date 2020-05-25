#ifndef SERVER_SECRETNUMBERS_H
#define SERVER_SECRETNUMBERS_H

#include "server_BlockingQueue.h"
#include <fstream>
#include <string>
#include <mutex>

class SecretNumbers {
private:
	BlockingQueue queue;
	std::ifstream fileName;
	std::mutex m;
	void load();

public:
	explicit SecretNumbers(const std::string& numbers);

	uint operator()();

	~SecretNumbers();

	SecretNumbers(SecretNumbers&& other);
	SecretNumbers& operator=(SecretNumbers&& other);

	SecretNumbers(const SecretNumbers& other) = delete;
	SecretNumbers &operator=(const SecretNumbers&) = delete;
};

#endif
