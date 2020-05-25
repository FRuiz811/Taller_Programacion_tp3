#include "server_Player.h"
#include "server_CommandHelp.h"
#include "server_CommandPlay.h"
#include "server_CommandSurrender.h"
#include <unistd.h>
#include <arpa/inet.h>
#include <utility>
#include <vector>

#define MAX_ATTEMPS 10

Player::Player(Socket socket, const uint number, Board& board) :
	secretNumber(number), keepTalking(true), board(board), attempts(0),
	protocol() {
		this->socket = std::move(socket);
	}


std::string Player::command_execute(char command) {
	Command* commandSelected = nullptr;
	switch(command) {
		case 'h':
			commandSelected = new CommandHelp();
			break;
		case 'n':
		{
			char numberAttempt[2];
			this->socket.recieve(&numberAttempt,2);
			uint16_t* temp16 = (uint16_t*) numberAttempt;
			ushort number = ntohs(*temp16);
			commandSelected = new CommandPlay(*this,this->secretNumber,number);
			this->attempts++;
		}
			break;
		case 's':
			commandSelected = new CommandSurrender(*this);
			break;
		default:
			delete commandSelected;
			throw std::exception();
	}
	std::string message = commandSelected->run();
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
		this->socket.recieve(&command,1);
		if (command == '\0')
			break;
		message = command_execute(command);
		if (message != "Ganaste" && this->attempts == MAX_ATTEMPS) {
			message = "Perdiste";
			add_loser();
			this->keepTalking = false;
		}
		std::vector<char> encoded = this->protocol.encode_string(message);
		this->socket.send(encoded.data(), encoded.size());		
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
