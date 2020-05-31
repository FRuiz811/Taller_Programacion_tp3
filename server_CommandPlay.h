#ifndef SERVER_COMMANDPLAY_H
#define SERVER_COMMANDPLAY_H

#include "server_Command.h"
#include "server_Player.h"
#include <string>

//CommandPlay maneja la parte lógica del juego.
class CommandPlay: public Command {
private:
	Player& player;
	uint secretNumber;
	uint attempt;

	int check_goods(std::string secret, std::string numberAttempt) const;
	int check_regulars(std::string secret, std::string numberAttempt) const;
public:
	//Recibe el jugador, el número secreto a adivinar y el intento del cliente
	CommandPlay(Player& player, uint secretNumber, uint attempt);

	//Si el intento del cliente no está dentro del rango entre 100 y 999
	//se lanzará una excepción del tipo std::out_of_range. Si el intento tiene
	//cifras repetidas lanzará una excepción del tipo std::invalid_argument.
	//En caso de que el intento sea correcto, devolverá el resultado del mismo.
	std::string execute();
	
	~CommandPlay();
};

#endif
