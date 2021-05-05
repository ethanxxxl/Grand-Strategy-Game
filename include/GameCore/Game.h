#ifndef GAME_H
#define GAME_H

#include <vector>
#include <GameCore/World.h>
#include <GameCore/GameObject.h>
#include <GameCore/Player.h>
#include <memory>

// TODO set this up so that it can be used in a client/server arrangement.
// this class is going to manager loading, saving, managing turns, verifying players, etc.
// it essentially manages the game.
class Game
{
private:
	// Game Data
	std::vector<Player> m_players;
	
	// whose turn is it?
	std::vector<Player>::iterator active_player;
	
	// the world
	World world;


public:
	// create a new game
	Game(std::vector<Player> players, int world_size);
	// load an existing game
	Game(std::string filename);
	
	void save();
	void save(std::string filename); // same as save, but you specify the filename

	// allows the player to play their turn, if it is their turn.
	void play_turn(std::string username);

	// get a list of valid moves of an object (referenced either by its ID or its pointer)
	std::vector<cube_coords_t> get_valid_moves(int ID);
	std::vector<cube_coords_t> get_valid_moves(GameObject* obj);

	// attempt to move the specified object. returns true if successful, false if not.
	bool move_object(int ID);
	bool move_object(GameObject* obj);
};

#endif
