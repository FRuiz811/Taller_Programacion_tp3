#include <iostream>
#include "client_Client.h"

#define INVALID_ARGUMENTS "Error: argumentos invalidos."

int main(int argc, char *argv[]) {
  if (argc != 3) {
  	std::cout << INVALID_ARGUMENTS << std::endl;
   	return 0;
  }

  Client client(argv[1], argv[2]);
  client.run();
  return 0;
}
