#include "Tile.h"
#include <Game.h>

#include <Player.h>
#include <SFML/Network/Packet.hpp>
#include <fstream>
#include <iterator>
#include <memory>
#include <vector>

Game::Game(std::vector<Player> players, int world_size) : world(world_size)
{
	// generate a world
	this->world_size = world_size;

	// set players
	this->players = players;
	active_player = players.begin();
}

int Game::get_world_size()
{
	return world_size;
}

Tile& Game::get_tile_at(int x, int y)
{
	return world.at(x,y);
}
