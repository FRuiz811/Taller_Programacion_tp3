#ifndef SERVER_PLAYER_H
#define SERVER_PLAYER_H

#include "server_Thread.h"
#include "common_Socket.h"
#include <atomic>

class Player : public Thread {
private:
	const uint secretNumber;
	std::atomic<bool> alive;
	std::atomic<bool> keepTalking;
public:
	Player(const uint number);

	bool is_alive() const;

	void stop();
	void run();

	~Player();
};

#endif
