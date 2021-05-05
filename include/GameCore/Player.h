#ifndef PLAYER_H
#define PLAYER_H

#include <GameCore/GameObject.h>
#include <GameCore/Player.h>
#include <string>
#include <vector>

class Player
{
private:
	// these things don't need to change
	std::string username;

public:
	/*
	 * Member Data
	 */
	//std::vector<GameObject&> objects;

	/*
	 * Constructors
	 */
	Player(std::string username);

	/*
	 * Methods
	 */
	std::string get_username(void);
};

#endif
