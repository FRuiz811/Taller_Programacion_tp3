#include <string>
#include <iostream>
#include "server_Server.h"

int main(int argc, char *argv[]) {
  if (argc != 3) {
  	std::cerr << "Error: argumentos invalidos.\n";
   	return 1;
  }
  
  const std::string fileNumbers = argv[2];
  Server server(argv[1], fileNumbers);
  server.run();
  return 0;
}
