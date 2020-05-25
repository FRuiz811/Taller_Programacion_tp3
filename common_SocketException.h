#ifndef COMMON_SOCKETEXCEPTION_H
#define COMMON_SOCKETEXCEPTION_H

#include <typeinfo>
#define BUFF_SIZE 256

class SocketException : public std::exception {
private: 
	char msg_error[BUFF_SIZE];
public:
	explicit SocketException(const char* msg, ...) noexcept;

	virtual const char* what() const noexcept;

	virtual~SocketException() noexcept;
};

#endif
