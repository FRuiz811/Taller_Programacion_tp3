#include "server_CommandHelp.h"
#include <sstream>

CommandHelp::CommandHelp() {}

std::string CommandHelp::execute() {
	std::stringstream help;
	help << "Comandos válidos:\n\tAYUDA: despliega la lista de comandos ";
	help << "válidos\n\tRENDIRSE: pierde el juego automáticamente\n\tXXX: ";
	help << "Número de 3 cifras a ser enviado al servidor para adivinar ";
	help << "el número secreto";
	return help.str();
}

CommandHelp::~CommandHelp() {}
