#include <string>
#include <iostream>
#include "server_Server.h"
#include <syslog.h>

#define INVALID_ARGUMENTS "Error: argumentos invalidos."
#define INVALID_FORMAT "Error: formato de los números invalidos"
#define INVALID_FILE "Error: archivo con números fuera de rango"
#define UNKNOW_ERROR "Unknow Error in server."
#define ERROR "Error: %s"

int main(int argc, char *argv[]) {
  if (argc != 3) {
  	std::cerr << INVALID_ARGUMENTS << std::endl;
   	return 1;
  }
  
  const std::string fileNumbers = argv[2];

  try{
  	Server server(argv[1], fileNumbers);
  	server.run();
  } catch(const std::invalid_argument& e) {
  	std::cerr << INVALID_FORMAT << std::endl;
  	syslog(LOG_CRIT, ERROR, e.what());
  	return 1;
  } catch (const std::out_of_range& e) {
  	std::cerr << INVALID_FILE << std::endl;
  	syslog(LOG_CRIT, INVALID_FILE);
  	return 1;
  } catch (...) {
  	syslog(LOG_CRIT, UNKNOW_ERROR);
  	return 1;
  }
  return 0;
}
