#ifndef GAME_H
#define GAME_H

#include <World.h>
#include <Player.h>
#include <Entity.h>
#include <memory>
#include <Tile.h>

// TODO set this up so that it can be used in a client/server arrangement.
// this class is going to manager loading, saving, managing turns, verifying players, etc.
// it essentially manages the game.

/* SYNOPSIS
 * this will be the to level logical block for this application. This will verify game moves,
 * keep track of entities, players, the map, etc.
 *
 * it will not handle drawing or user input.
 */

class Game
{
private:
	// list of all players in the game
	std::vector<Player> players;
	
	// whose turn is it?
	std::vector<Player>::iterator active_player;
	
	// contains all entities
	//std::vector<Entity> entities;
	
	// the world
	World world;


	int world_size;
public:
	// create a new game
	Game(std::vector<Player> players, int world_size);
	// load an existing game
	Game(std::string filename);

	int get_world_size();
	Tile& get_tile_at(int x, int y);

	void schedule_move();
	void commit_move();

	void save();
	void save(std::string filename); // same as save, but you specify the filename
};

#endif
