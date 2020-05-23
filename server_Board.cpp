#include "server_Board.h"
#include <utility>
#include <iostream>

Board::Board() : winners(0), losers(0) {}


void Board::add_winner() {
	std::unique_lock<std::mutex> lock(m);
	this->winners++;
}

void Board::add_loser() {
	std::unique_lock<std::mutex> lock(m);
	this->losers++;
}

void Board::show_results() {
	std::cout << "Estadísticas:\n";
	std::cout << "\tGanadores:  "<< this->winners <<"\n";
	std::cout << "\tPerdedores: " << this->losers <<"\n";
}

Board::Board(Board&& other) {
	this->winners = std::move(other.winners);
	this->losers = std::move(other.losers);
}

Board& Board::operator=(Board&& other) {
	this->winners = std::move(other.winners);
	this->losers = std::move(other.losers);
	return *this;
}


Board::~Board() {}