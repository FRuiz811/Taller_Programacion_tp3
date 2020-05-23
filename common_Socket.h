#ifndef COMMON_SOCKET_H
#define COMMON_SOCKET_H

#include <cstdint>

class Socket {
private:
	int fd;

	void resolve_address(struct addrinfo* hints,
						const char* host, const char* port);

	explicit Socket(int fd);
public:
	Socket();
	Socket(Socket&& other);
	Socket& operator=(Socket&& other);

	void bind_and_listen(const char* port, std::uint32_t max_waiting);
	void connect(const char* host, const char* port);
	Socket accept();
	int send(const void* buffer, std::uint32_t length) const;
	int recieve(void* buffer, std::uint32_t length) const;
	void shutdown(int channel);
	void close();
	~Socket();

	Socket(const Socket& other) = delete;
	Socket& operator=(const Socket& other) = delete;
};

#endif
