#include "server_CommandPlay.h"
#include <sstream>

#define INVALID_NUMBER "Número inválido. Debe ser de 3 cifras no repetidas"
#define WINNER "Ganaste"

CommandPlay::CommandPlay(Player& player, uint number, uint attempt) :
	player(player), secretNumber(number), attempt(attempt) {}

int CommandPlay::check_goods(std::string secret, 
														 std::string numberAttempt) const {
	int good = 0;
	for (int i = 0; i < 3; i++) {
		if (secret[i] == numberAttempt[i])		
			good++;
	}
	return good;
}

int CommandPlay::check_regulars(std::string secret, 
															 std::string numberAttempt) const {
	int regular = 0;
	if (numberAttempt[0] == secret[1] || numberAttempt[0] == secret[2]) 
		regular++;
	if (numberAttempt[1] == secret[2] || numberAttempt[1] == secret[0])
		regular++;
	if (numberAttempt[2] == secret[1] || numberAttempt[2] == secret[0]) 
		regular++;
	return regular;
}

std::string CommandPlay::execute() {
	std::string secret = std::to_string(this->secretNumber);
	std::string numberAttempt = std::to_string(this->attempt);
	std::stringstream message;
	if (this->attempt < 100 || this->attempt > 999 || 
			numberAttempt[0] == numberAttempt[1] ||
			numberAttempt[0] == numberAttempt[2] ||
			numberAttempt[1] == numberAttempt[2]) {
				message << INVALID_NUMBER;
				return message.str();
			}
	if (this->secretNumber == this->attempt) {
		message << WINNER;
		this->player.stop();
		this->player.add_winner();
		return message.str();
	}
	int good = check_goods(secret,numberAttempt);
	int regular = check_regulars(secret, numberAttempt);
	if (good == 0 && regular == 0) 
		message << "3 mal";
	if (good != 0) 
		message << good << " bien";
	if (good != 0 && regular != 0) 
		message << ", ";
	if (regular != 0) 
		message << regular << " regular";
	return message.str();
}

CommandPlay::~CommandPlay() {}
