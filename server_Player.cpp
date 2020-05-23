#include "server_Player.h"
#include <iostream>
#include <unistd.h>

Player::Player(const uint number) : secretNumber(number) , alive(true) ,
	keepTalking(true) {}


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