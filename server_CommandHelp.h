#ifndef SERVER_COMMANDHELP_H
#define SERVER_COMMANDHELP_H

#include "server_Command.h"
#include <string>

class CommandHelp: public Command {
public:
	CommandHelp();

	std::string execute();
	
	~CommandHelp();
};

#endif
