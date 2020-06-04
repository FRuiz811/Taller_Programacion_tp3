#include "server_CommandHelp.h"
#include <sstream>

#define COMANDS "Comandos válidos:\n"
#define HELP "\tAYUDA: despliega la lista de comandos válidos\n"
#define SURRENDER "\tRENDIRSE: pierde el juego automáticamente\n"
#define XXX "\tXXX: Número de 3 cifras a ser enviado al servidor "\
			"adivinar el número secreto"
			
CommandHelp::CommandHelp() {}

std::string CommandHelp::execute() {
	std::stringstream help;
	help << COMANDS;
	help << HELP;
	help << SURRENDER;
	help << XXX;
	return help.str();
}

CommandHelp::~CommandHelp() {}
