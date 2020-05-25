#ifndef COMMON_SOCKET_H
#define COMMON_SOCKET_H

#include <cstdint>

class Socket {
private:
	int fd;
	//Resuelve la conexión con el host (si es indicado) y el puerto al cual el
	//soquet se conecta. El file descriptor que es utilizado queda almacenado
	//en el Socket.
	void resolve_address(struct addrinfo* hints,
						const char* host, const char* port);

	//Contructor solamente utilizado en accept.
	explicit Socket(int fd);

public:
	//Constructores de Socket. Se elimina el constructor por copia.
	//En caso de los constructores por movimiento se invalida a other
	//tomando el ownership del mismo.
	Socket();
	Socket(Socket&& other);
	Socket& operator=(Socket&& other);

	//Se encarga de conectar el socket aceptador (del lado del servidor)
	//con el puerto indicado como parámetro e indicarle la cantidad máxima
	//de conexiones en espera que puede haber a la vez. Lanza una 
	//SocketException en caso de error.
	void bind_and_listen(const char* port, std::uint32_t max_waiting);

	//Se encarga de conectar el cliente con el (host, port) indicando como
	//parámetro. Lanza una SocketException en caso de error.
	void connect(const char* host, const char* port);

	//Acepta la conexión de un cliente. Devuelve al Socket por movimiento.
	//Lanza una SocketException en caso de error.
	Socket accept();

	//Envía un stream que comienza en buffer de longitud length.
	//Devuelve la cantidad de bytes enviados.
	//Lanza una SocketException en caso de error.
	int send(const void* buffer, std::uint32_t length) const;

	//Almacena en un buffer de longitud length todos los bytes
	//recibidos en el socket self. devuelve la cantidad de bytes recibidos.
	//Lanza una SocketException en caso de error.
	int recieve(void* buffer, std::uint32_t length) const;

	//channel: SHUT_WR, SHUT_RD, SHUT_RDWR
	void shutdown(int channel);

	//Realiza un cierre del Socket, invalidandolo.
	void close();
	
	~Socket();

	Socket(const Socket& other) = delete;
	Socket& operator=(const Socket& other) = delete;
};

#endif
