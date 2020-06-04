#include "common_Socket.h"
#include "common_SocketException.h"
#include <utility>
#include <cstring>
#include <unistd.h>
#include <stdexcept>
#include <netdb.h>
#include <sys/socket.h>

#define FAIL_FD "No se pudo conectar a ningún file descriptor."
#define FAIL_GETADRR "Error en getaddrinfo."
#define FAIL_BIND "Error al realizar el bind al puerto %s."
#define FAIL_CONNECT "Error al conectarse al host %s y puerto %s."
#define FAIL_ACCEPT "Error al intentar aceptar un nuevo cliente."
#define FAIL_SEND "Error al enviar desde el socket %d."
#define FAIL_RECV "Error al recibir desde el socket %d."

Socket::Socket() : fd(-1) {}

Socket::Socket(int fd) : fd(fd) {}

void Socket::resolve_address(struct addrinfo* hints, 
	                        const char* host, const char* port) {
	struct addrinfo *results, *iter;
	int val = 1;
	if (getaddrinfo(host, port, hints, &results) != 0) {
		freeaddrinfo(results);
		throw SocketException(FAIL_GETADRR);
	}
	
	for (iter = results; iter != nullptr; iter = iter->ai_next) {
		this->fd = ::socket(iter->ai_family,iter->ai_socktype,0);

		if (this->fd == -1)
			continue;

		if(host == nullptr) {
			if (::bind(this->fd, iter->ai_addr, iter->ai_addrlen) == 0) {
				setsockopt(this->fd, SOL_SOCKET,SO_REUSEADDR, &val, sizeof(val));
				break;
			}
		} else {
			if(::connect(this->fd, iter->ai_addr, iter->ai_addrlen) != -1)
				break;
		}
		::close(this->fd);
		this->fd = -1;
	}

	freeaddrinfo(results);
	if(this->fd == -1) 
		throw SocketException(FAIL_FD);
	return;
}

void Socket::bind_and_listen(const char* port, std::uint32_t max_waiting) {
	struct addrinfo hints;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET; //IPv4
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	try{
		resolve_address(&hints, nullptr, port);
	} catch (const SocketException& e) {
		throw SocketException(FAIL_BIND, port);
	}	
	::listen(this->fd, max_waiting);
	
	return;
}

void Socket::connect(const char* host, const char* port) {
	struct addrinfo hints;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET; //IPv4	
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = 0;
	try{
		resolve_address(&hints, host, port);
	} catch (const SocketException& e) {
		throw SocketException(FAIL_CONNECT, host, port);
	}
	return;
}

Socket Socket::accept() {
	int new_fd = ::accept(this->fd, nullptr, nullptr);
	if (new_fd == -1)
		throw SocketException(FAIL_ACCEPT);
	return std::move(Socket(new_fd));
}

int Socket::send(const void* buffer, std::uint32_t length) const {
	std::uint32_t sended_bytes = 0;
	int result_send;
	std::uint32_t remaining_bytes = length;
	const char* char_buffer = (const char*) buffer;
	while(sended_bytes < length) {
		result_send = ::send(this->fd, &char_buffer[sended_bytes],
						   remaining_bytes, MSG_NOSIGNAL);
		if(result_send == -1 || result_send == 0)
			throw SocketException(FAIL_SEND, this->fd);
		sended_bytes += result_send;
		remaining_bytes -= result_send;
	}
	return sended_bytes;
}

int Socket::recieve(void* buffer, std::uint32_t length) const {
	std::uint32_t received_bytes = 0;
	int result_recv;
	std::uint32_t remaining_bytes = length;
	char* char_buffer = (char*) buffer;

	while(received_bytes < length) {
		result_recv = ::recv(this->fd, &char_buffer[received_bytes],
						   remaining_bytes, 0);
		if(result_recv == -1 || result_recv == 0)
			throw SocketException(FAIL_RECV,this->fd);
		received_bytes += result_recv;
		remaining_bytes -= result_recv;
	}
	return received_bytes;
}

Socket::Socket(Socket&& other) : fd(other.fd) {
	other.fd = -1;
}

Socket& Socket::operator=(Socket&& other) {
	this->fd = other.fd;
	other.fd = -1;
	return *this;
}

void Socket::shutdown(int channel) {
	::shutdown(this->fd, channel); 
}

void Socket::close() {
	if (this->fd != -1){
		shutdown(SHUT_RDWR);
		::close(this->fd);
	}
	this->fd = -1;
}

Socket::~Socket() {
	this->close();
}
