#ifndef SERVER_SECRETNUMBERS_H
#define SERVER_SECRETNUMBERS_H

#include "server_BlockingQueue.h"
#include <fstream>
#include <string>
#include <mutex>

//SecretNumbers es la clase encargada de procesar el archivo con los números
//secretos. Chequea que cada uno de los números tenga un formato válido y este
//dentro del rango entre 100 y 999.
//Utiliza una cola bloqueante para que los Players obtengan sus números 
//ordenadamente.
class SecretNumbers {
private:
	BlockingQueue queue;
	std::ifstream fileName;
	std::mutex m;
	
	//Si el número del archivo no está dentro del rango entre 100 y 999
	//se lanzará una excepción del tipo std::out_of_range. Si el número tiene
	//cifras repetidas lanzará una excepción del tipo std::invalid_argument.
	void load();

public:
	explicit SecretNumbers(const std::string& numbers);

	//Devuelve el próximo número secreto y lo vuelve a colocar en la queue
	//para respetar el formato round robin.
	uint operator()();

	~SecretNumbers();

	SecretNumbers(SecretNumbers&& other);
	SecretNumbers& operator=(SecretNumbers&& other);

	SecretNumbers(const SecretNumbers& other) = delete;
	SecretNumbers &operator=(const SecretNumbers&) = delete;
};

#endif
