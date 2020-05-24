#include "server_CommandHelp.h"

CommandHelp::CommandHelp() {}

std::string CommandHelp::run() {
	std::string help = "Comandos válidos:​\n\t​AYUDA: despliega la ";
	help += "lista de comandos válidos​\n\t​RENDIRSE: pierde el juego ";
	help += "automáticamente​\n\t​XXX: Número de 3 cifras a ser enviado al servidor ";
	help += "para adivinar el número secreto";
	return help;
}

CommandHelp::~CommandHelp() {}