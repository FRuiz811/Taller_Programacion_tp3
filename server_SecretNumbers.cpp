#include "server_SecretNumbers.h"
#include <string>
#include <fstream>
#include <utility>

SecretNumbers::SecretNumbers(const std::string& numbers) : queue(), 
	fileName(numbers, std::ifstream::in) {
		load();
}

void SecretNumbers::load() {
	std::string number_read;
	uint number = 0;
	while (this->fileName.good()) {
		getline(this->fileName,number_read);
		if (number_read[0] == number_read[1] ||
			number_read[0] == number_read[2] ||
			number_read[1] == number_read[2]) {
			throw std::exception();
		}
		number = std::stoi(number_read);
		if (number < 100 || number > 999)
			throw std::exception();
		this->queue.push(number);
	}
	this->queue.close();
	this->fileName.seekg(0);
}

uint SecretNumbers::operator()() {
	std::unique_lock<std::mutex> lock(m);
	uint next_number = 0;
	next_number = this->queue.pop();
	this->queue.push(next_number);
	return next_number;
}

SecretNumbers::~SecretNumbers() {
	if (this->fileName.is_open()) {
		this->fileName.close();
	}
}
