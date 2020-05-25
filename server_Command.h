#ifndef SERVER_COMMAND_H
#define SERVER_COMMAND_H

#include <string>
class Command {
public:
	Command();

	virtual std::string execute() = 0;
	
	virtual	~Command();
};

#endif
