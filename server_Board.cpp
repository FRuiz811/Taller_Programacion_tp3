#include "server_Board.h"
#include <utility>
#include <iostream>

#define STATS "Estadísticas:"
#define WINNERS "\tGanadores:  "
#define LOSERS "\tPerdedores: "

Board::Board() : winners(0), losers(0) {}

void Board::add_winner() {
	std::unique_lock<std::mutex> lock(m);
	this->winners++;
}

void Board::add_loser() {
	std::unique_lock<std::mutex> lock(m);
	this->losers++;
}

void Board::show_results() const {
	std::unique_lock<std::mutex> lock(m);
	std::cout << STATS << std::endl;
	std::cout << WINNERS << this->winners << std::endl;
	std::cout << LOSERS << this->losers << std::endl;
}

Board::Board(Board&& other) {
	std::unique_lock<std::mutex> lock(m);
	this->winners = std::move(other.winners);
	this->losers = std::move(other.losers);
}

Board& Board::operator=(Board&& other) {
	std::unique_lock<std::mutex> lock(m);
	this->winners = std::move(other.winners);
	this->losers = std::move(other.losers);
	return *this;
}


Board::~Board() {}
