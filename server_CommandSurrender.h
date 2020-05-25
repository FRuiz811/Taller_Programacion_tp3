#ifndef SERVER_COMMANDSURRENDER_H
#define SERVER_COMMANDSURRENDER_H

#include "server_Command.h"
#include "server_Player.h"
#include <string>

//CommandSurrender es la encargada de frenar el juego porque el cliente.
//asi lo indicó. Le indica al Player que deje de hablar con este cliente.
//Agrega un perdedor a las estadísticas.
class CommandSurrender: public Command {
private:
	Player& player;
public:
	explicit CommandSurrender(Player& player);

	std::string execute();
	~CommandSurrender();
};

#endif
