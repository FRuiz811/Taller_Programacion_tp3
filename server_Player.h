#ifndef SERVER_PLAYER_H
#define SERVER_PLAYER_H

#include "server_Thread.h"
#include "common_Socket.h"
#include <atomic>
#include "server_Board.h"

class Player : public Thread {
private:
	const uint secretNumber;
	std::atomic<bool> alive;
	std::atomic<bool> keepTalking;
	Board& board;
	int attempts;
	
public:
	Player(const uint number, Board& board);

	bool is_alive() const;

	void stop();
	void run();

	~Player();
};

#endif
