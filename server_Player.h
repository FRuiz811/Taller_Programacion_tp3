#ifndef SERVER_PLAYER_H
#define SERVER_PLAYER_H

#include "server_Thread.h"
#include "common_Socket.h"
#include "server_Board.h"
#include "server_Command.h"
#include "common_Protocol.h"
#include <atomic>
#include <string>

//La clase Player es la que se encarga de jugar la partida contra el cliente.
//Lleva el control de que el cliente no juegue más veces que los intentos 
//permitidos y solamente conoce el número secreto que el cliente tiene que 
//adivinar. 
class Player : public Thread {
private:
	Socket socket;
	const uint secretNumber;
	std::atomic<bool> keepTalking;
	Board& board;
	int attempts;
	Protocol protocol;

	//Devuelve el string del comando ejecutado.
	//Lanzará una excepción en cado de que el comando ingresado no sea
	//correcto.
	std::string command_execute(char command);

public:
	//Mueve el socket recibido como parámetro y se hace ownership del mismo.
	Player(Socket socket, const uint number, Board& board);

	bool is_alive() const;

	//Se le indica que deje de comunicarse con el cliente, pero no se realiza 
	//el cierre del socket.
	void stop();

	//Se establece la comunicación con el cliente, recibiendo sus comandos
	//y enviando las respuestas correspondientes. Valida que se siga dentro
	//del máximo de intentos.
	virtual void run();

	void add_loser();
	
	void add_winner();
	
	virtual ~Player();

	Player(const Player& other) = delete;
	Player& operator=(const Player& other) = delete;
};

#endif
