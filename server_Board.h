#ifndef SERVER_BOARD_H
#define SERVER_BOARD_H

#include <mutex>

class Board {
private:
	uint winners;
	uint losers;
	std::mutex m;
	
public:
	Board();
	Board(Board&& other);
	Board& operator=(Board&& other);

	void add_winner();
	void add_loser();

	void show_results();
	~Board();

	Board(const Board& other) = delete;
	Board &operator=(const Board&) = delete;
};

#endif
