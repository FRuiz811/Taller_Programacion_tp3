#include "server_CommandSurrender.h"

#define LOSER "Perdiste"

CommandSurrender::CommandSurrender(Player& player) : player(player) {}

std::string CommandSurrender::execute() {
	std::string message = LOSER;
	this->player.add_loser();
	this->player.stop();
	return message;
}

CommandSurrender::~CommandSurrender() {}
