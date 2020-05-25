#ifndef SERVER_H
#define SERVER_H

#include "server_SecretNumbers.h"
#include "server_GamesAcceptor.h"
#include "server_Board.h"
#include <string>

//La clase Server es la encargada de realizar la gestión básica del juego.
//Se encarga de realizar el procesamiento del archivo con los numeros 
//secretos, y muestra las estadísticas una vez cerrado el mismo. 
//Lanzará un thread que será el encargado de aceptar los clientes.
class Server {
private:
	SecretNumbers numbers;
	Board board;
	GamesAcceptor gamesAcceptor;
public:
	//Es el único constructor de la clase, se le indica el puerto por el
	//cual escuchará a sus clientes y el nombre del archivo a abrir.
	//Lanza a ejecutar el gamesAcceptor.
	explicit Server(const char* port, const std::string& fileNumbers);

	//Se ejecutará hasta que se ingrese una 'q' por entrada estándar.
	//Mostrará las estadísticas por salida estándar.
	void run();

	~Server();
	Server(Server&& other) = delete;
	Server& operator=(Server&& other) = delete;
	Server(const Server& other) = delete;
	Server& operator=(const Server& other) = delete;
};

#endif
