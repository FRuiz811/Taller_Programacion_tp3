#include "server_CommandHelp.h"
#include <sstream>

CommandHelp::CommandHelp() {}

std::string CommandHelp::run() {
	std::stringstream help;
	help << "Comandos válidos:​\n\t​AYUDA: despliega la ";
	help << "lista de comandos válidos​\n\t​RENDIRSE: pierde el juego ";
	help << "automáticamente​\n\t​XXX: Número de 3 cifras a ser enviado al";
	help << " servidor para adivinar el número secreto";
	return help.str();
}

CommandHelp::~CommandHelp() {}
