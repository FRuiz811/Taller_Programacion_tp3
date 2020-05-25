#include <string>
#include <iostream>
#include "server_Server.h"
#include <syslog.h>

int main(int argc, char *argv[]) {
  if (argc != 3) {
  	std::cerr << "Error: argumentos invalidos.\n";
   	return 1;
  }
  
  const std::string fileNumbers = argv[2];

  try{
  	Server server(argv[1], fileNumbers);
  	server.run();
  } catch(const std::invalid_argument& e) {
  	std::cerr << "Error: formato de los números invalidos\n";
  	syslog(LOG_CRIT, "Error: %s", e.what());
  	return 1;
  } catch (const std::out_of_range& e) {
  	std::cerr << "Error: archivo con números fuera de rango\n";
  	syslog(LOG_CRIT, "Invalid number format in file.\n");
  } catch (...) {
  	syslog(LOG_CRIT, "Unknow Error in server.");
  	return 1;
  }
  return 0;
}
