#include "server_Player.h"
#include <iostream>
#include <unistd.h>

#define MAX_ATTEMPS 10

Player::Player(const uint number, Board& board) : secretNumber(number), 
	alive(true), keepTalking(true), board(board), attemps(0) {}


bool Player::is_alive() const {
	return this->alive;
}
void Player::run(){
	std::cout << this->secretNumber <<"\n";
	while(keepTalking) {
	}
	std::cout << this->keepTalking <<"\n";
}

void Player::stop() {
	this->keepTalking = false;
}

Player::~Player() {

}