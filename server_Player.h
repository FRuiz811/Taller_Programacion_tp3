#ifndef SERVER_PLAYER_H
#define SERVER_PLAYER_H

#include "server_Thread.h"
#include "common_Socket.h"
#include <atomic>
#include "server_Board.h"
#include "server_Command.h"
#include "common_Protocol.h"

class Player : public Thread {
private:
	Socket socket;
	const uint secretNumber;
	std::atomic<bool> keepTalking;
	Board& board;
	int attempts;
	Protocol protocol;

	std::string command_execute(char command);

public:
	Player(Socket socket, const uint number, Board& board);

	bool is_alive() const;
	void stop();
	virtual void run();
	void add_loser();
	void add_winner();
	virtual ~Player();

	Player(const Player& other) = delete;
	Player& operator=(const Player& other) = delete;
};

#endif
