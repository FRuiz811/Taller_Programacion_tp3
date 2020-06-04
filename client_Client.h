#ifndef CLIENT_H
#define CLIENT_H

#include "common_Socket.h"
#include "common_Protocol.h"
#include <cstdint>
#include <string>
#include <atomic>

//La clase Client es la encargada de interactuar con el usuario.
//Esperará por la entrada estándar los comandos que le permitirán adivinar
//el número secreto.
class Client {
private:
	Socket socket;
	Protocol protocol;
	std::atomic<bool> keep_talking;
	//Se encarga de la comunicación con el servidor, llamando al protocolo
	//que será el encargado de encodear el mensaje que se le enviará al 
	//servidor. En caso de error lanzará una excepción
	void send_message(const std::string& command);

	//Devolverá como string el mensaje recibido por el servidor.
	std::string recieve_message();
	
public:
	//Se conectará al host y port indicado como parámetros para poder jugar
	//contra el servidor.
	explicit Client(const char* host, const char* port);

	//Se encarga de recibir la procesar la entrada estándar y de imprimir
	//los resultados devueltos por el servidor. 
	void run();

	~Client();

	Client(Client&& other) = delete;
	Client& operator=(Client&& other) = delete;
	Client(const Client& other) = delete;
	Client& operator=(const Client& other) = delete;
};

#endif
