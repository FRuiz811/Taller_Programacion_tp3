#ifndef SERVER_COMMANDSURRENDER_H
#define SERVER_COMMANDSURRENDER_H

#include "server_Command.h"
#include "server_Player.h"
#include <string>

class CommandSurrender: public Command {
private:
	Player& player;
public:
	CommandSurrender(Player& player);

	std::string run();
	~CommandSurrender();
};

#endif
