#ifndef GAME_H
#define GAME_H

#include <World.h>
#include <Player.h>
#include <memory>

// TODO set this up so that it can be used in a client/server arrangement.
// this class is going to manager loading, saving, managing turns, verifying players, etc.
// it essentially manages the game.


class Game
{
private:
	// list of all players in the game
	std::vector<Player> players;
	
	// whose turn is it?
	std::vector<Player>::iterator active_player;
	
	// the world
	std::shared_ptr<World> world;

public:
	// create a new game
	Game(std::vector<Player> players, int world_size);
	// load an existing game
	Game(std::string filename);

	// allows the player to play their turn, if it is their turn.
	void play_turn(std::string username);

	void save();
	void save(std::string filename); // same as save, but you specify the filename
};

#endif
