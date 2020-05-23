#ifndef SERVER_GAMESACCEPTOR_H
#define SERVER_GAMESACCEPTOR_H

#include "server_Thread.h"
#include "server_SecretNumbers.h"
#include "common_Socket.h"
#include "server_Player.h"
#include <vector>
#include <atomic>

class GamesAcceptor: public Thread {
private:
	Socket socket;
	SecretNumbers& secretNumbers;
	std::vector<Player*> players;
	std::atomic<bool> keepTalking;

	void clear_finished_games();
	void stop_players();

public:
	explicit GamesAcceptor(const char* port, SecretNumbers& secretNumbers);

	void run();

	void stop();

	~GamesAcceptor();

};

#endif
