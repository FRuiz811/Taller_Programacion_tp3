#ifndef SERVER_COMMANDPLAY_H
#define SERVER_COMMANDPLAY_H

#include "server_Command.h"
#include "server_Player.h"
#include <string>

class CommandPlay: public Command {
private:
	Player& player;
	uint secretNumber;
	uint attempt;

	int check_goods(std::string secret, std::string numberAttempt) const;
	int check_regulars(std::string secret, std::string numberAttempt) const;
public:
	CommandPlay(Player& player, uint secretNumber, uint attempt);

	std::string execute();
	~CommandPlay();
};

#endif
