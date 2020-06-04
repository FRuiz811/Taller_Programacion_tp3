#ifndef COMMON_PROTOCOL_H
#define COMMON_PROTOCOL_H

#include <string>
#include <vector>

//Protocol es la clase encargada de encodear el envio de los mensajes
//que se utilizaran para la comunicación entre Server y Client.
class Protocol {
private:
	std::vector<char> message;
public:
	Protocol();
	
	//Al comando recibido como parámetro lo encodea a su letra correspondiente
	//En caso de que sea un número, colocará su respectiva letra y luego lo 
	//intentará convertir a un short int en formato big endian y en caso que  
	//no pueda, lanzará una excepción. Devuelve, por moviemiento, un 
	//vector<char> con el mensaje encodeado.
	std::vector<char> encode_command(const std::string& command);

	//Al mensaje recibido como parmámetro lo encodea colocando su longitud en
	//los primeros 4 bytes del encoding, en formato big endian y luego sigue 
	//el string a encodear sin agregar el \0.  Devuelve, por moviemiento, un 
	//vector<char> con el mensaje encodeado.
	std::vector<char> encode_string(const std::string& messageToEncode);

	~Protocol();
	Protocol(const Protocol& other) = delete;
	Protocol& operator=(const Protocol& other) = delete;
};

#endif
