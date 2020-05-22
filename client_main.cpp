#include <string>
#include <iostream>
#include "client_Client.h"

int main(int argc, char *argv[]) {
  if (argc != 3) {
  	std::cout << "Error: argumentos invalidos.\n";
   	return 0;
  }

  Client client(argv[1], argv[2]);
  client.run();
  return 0;
}
