#include "server_CommandSurrender.h"

CommandSurrender::CommandSurrender(Player& player) : player(player) {}

std::string CommandSurrender::run() {
	std::string message = "Perdiste";
	this->player.add_loser();
	this->player.stop();
	return message;
}

CommandSurrender::~CommandSurrender() {}