#include "server_GamesAcceptor.h"
#include <sys/socket.h>

#define MAX_WAITING 20

GamesAcceptor::GamesAcceptor(const char* port, SecretNumbers& secretNumbers) :
 	socket() , secretNumbers(secretNumbers), players(), keepTalking(true),
 	board() {
	this->socket.bind_and_listen(port, MAX_WAITING);
}

void GamesAcceptor::clear_finished_games() {
	std::vector<Player*> temp;
	std::vector<Player*>::iterator it = this->players.begin();
	for (;it != this->players.end(); ++it) {
		if ((*it)->is_alive()){
			temp.push_back(*it);
		}
	}
	this->players.swap(temp);
	it = temp.begin();
	for (;it != temp.end(); ++it) {
		if (!(*it)->is_alive()) {
			(*it)->join();
			delete (*it);
		}
	}
}

void GamesAcceptor::run() {
	while (this->keepTalking){
		try{
			Socket socketPlayer = this->socket.accept();
			Player* player = new Player(std::move(socketPlayer), secretNumbers(), this->board);
			this->players.push_back(player);
			player->start();
			clear_finished_games();
		} catch (const std::exception& e) {
			break;
		}
	}
}

void GamesAcceptor::stop_players() {
	for (size_t i = 0; i < this->players.size(); i++) {
		this->players[i]->stop();
    this->players[i]->join();
    delete this->players[i];
  }
}

void GamesAcceptor::stop() {
	this->keepTalking = false;
	this->socket.shutdown(SHUT_RDWR);
	this->socket.close();
	stop_players();
	this->board.show_results();
}

GamesAcceptor::~GamesAcceptor() {}