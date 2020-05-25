#ifndef SERVER_COMMAND_H
#define SERVER_COMMAND_H

#include <string>
class Command {
public:
	Command();

	virtual std::string run() = 0;
	
	virtual	~Command();
};

#endif
