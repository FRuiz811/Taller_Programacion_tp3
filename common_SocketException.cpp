#include "common_SocketException.h"
#include <errno.h>
#include <cstdio>
#include <cstring>
#include <cstdarg>

SocketException::SocketException(const char* msg, ...) noexcept {
	int _errno = errno;

	va_list args;
	va_start(args, msg);
	int s = vsnprintf(msg_error, BUFF_SIZE, msg, args);
	va_end(args);

	strncpy(msg_error+s, strerror(_errno), BUFF_SIZE-s);
	msg_error[BUFF_SIZE-1] = 0;
}

const char* SocketException::what() const noexcept {
	return msg_error;
}

SocketException::~SocketException() noexcept {}