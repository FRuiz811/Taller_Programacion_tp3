#ifndef SERVER_GAMESACCEPTOR_H
#define SERVER_GAMESACCEPTOR_H

#include "server_Thread.h"
#include "server_SecretNumbers.h"
#include "common_Socket.h"
#include "server_Player.h"
#include "server_Board.h"
#include <vector>
#include <atomic>

//GamesAcceptor es el hilo encargado de aceptar a cada uno de los clientes
//que quieran jugar. A medida que va aceptado lanzará los hilos Players.
class GamesAcceptor: public Thread {
private:
	Socket socket;
	SecretNumbers& secretNumbers;
	std::vector<Player*> players;
	std::atomic<bool> keepTalking;
	Board& board;

	//Elimina los jugadores que ya terminaron su partida contra el cliente.
	//Libera la memoria de los Player* players que ya no estén activos.
	void clear_finished_games();

	//Se le indica a todos los players que dejen de hablar con los clientes.
	//Se realiza el join correspondientes y se libera la memoria allocada.
	void stop_players(); 
	
public:
	//Constructor explicito de la clase GamesAcceptor.
	explicit GamesAcceptor(const char* port, 
						   SecretNumbers& secretNumbers, Board& board);
	
	//Se irán aceptando clientes y a medida que esto suceda se lanzaran
	//los players que quedarán allocados en el heap.
	virtual void run();

	//Se realiza el cierre del socket aceptador y se procede a realizar el
	//join de los players.
	void stop();

	virtual ~GamesAcceptor();
};

#endif
