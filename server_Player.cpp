#include "server_Player.h"
#include "server_CommandHelp.h"
#include "server_CommandPlay.h"
#include "server_CommandSurrender.h"
#include "common_SocketException.h"
#include <unistd.h>
#include <arpa/inet.h>
#include <utility>
#include <vector>
#include <syslog.h>

#define MAX_ATTEMPS 10
#define COMMAND_HELP 'h'
#define COMMAND_SURRENDER 's'
#define COMMAND_PLAY 'n'
#define INVALID_COMMAND "Error comando ingresado incorrecto: "
#define LOSER "Perdiste"
#define WINNER "Ganaste"
#define UNKNOW_ERROR "Unknow error in Player"
#define ERROR "Error: %s"
#define CLIENT_OUT "El cliente se fue: %s"

Player::Player(Socket socket, const uint number, Board& board) :
	secretNumber(number), keepTalking(true), board(board), attempts(0),
	protocol() {
		this->socket = std::move(socket);
	}


std::string Player::command_execute(char command) {
	Command* commandSelected = nullptr;
	switch(command) {
		case COMMAND_HELP:
			commandSelected = new CommandHelp();
			break;
		case COMMAND_PLAY:
		{
			char numberAttempt[2];
			this->socket.recieve(&numberAttempt,2);
			uint16_t* temp16 = (uint16_t*) numberAttempt;
			ushort number = ntohs(*temp16);
			commandSelected = new CommandPlay(*this,this->secretNumber,number);
			this->attempts++;
		}
			break;
		case COMMAND_SURRENDER:
			commandSelected = new CommandSurrender(*this);
			break;
		default:
			delete commandSelected;
			std::string error = INVALID_COMMAND + command;
			throw std::invalid_argument(error);
	}
	std::string message = commandSelected->execute();
	delete commandSelected;
	return message;
}


bool Player::is_alive() const {
	return this->keepTalking;
}

void Player::run(){
	char command = '\0';
	std::string message;
	while(keepTalking) {
		try{
			this->socket.recieve(&command,1);
			if (command == '\0')
				break;
			message = command_execute(command);
			if (message != WINNER && this->attempts == MAX_ATTEMPS) {
				message = LOSER;
				add_loser();
				this->keepTalking = false;
			}
			std::vector<char> encoded = this->protocol.encode_string(message);
			this->socket.send(encoded.data(), encoded.size());		
		} catch (const SocketException& e) {
			add_loser();
			this->keepTalking = false;
			syslog(LOG_INFO, CLIENT_OUT, e.what());
	  }	catch (const std::exception& e) {
				add_loser();
				this->keepTalking = false;
				syslog(LOG_CRIT, ERROR, e.what());
		} catch(...) {
			syslog(LOG_CRIT, UNKNOW_ERROR);
		}
	}
}

void Player::add_winner() {
	this->board.add_winner();
}

void Player::add_loser() {
	this->board.add_loser();
}

void Player::stop() {
	this->keepTalking = false;
}

Player::~Player() {}
