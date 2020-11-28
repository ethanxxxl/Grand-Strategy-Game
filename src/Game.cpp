#include <Game.h>

#include <Player.h>
#include <SFML/Network/Packet.hpp>
#include <fstream>
#include <iterator>
#include <memory>
#include <vector>

Game::Game(std::vector<Player> players, int world_size)
{
	// generate a world
	world = std::make_shared<World>(world_size, world_size);

	// set players
	this->players = players;
	active_player = players.begin();

	// give all of the players a reference to the world
	for ( auto p = players.begin(); p != players.end(); ++p )
	{
		p->world = world;
	}
}

void Game::play_turn(std::string username)
{
	for ( auto n = players.begin(); n != players.end(); ++n )
	{
		// I know that this is not secure at all, but whatever, it is easy.
		if ( n->get_username().compare(username) )
		{
			// it is not this players turn
			if ( n != active_player )
			{
				// just return from the function.
				//  maybe later, send a copy of the updated game board, or something
				return;
			}

			break;
		}
	}

	// if execution gets here, then that means that it is the players turn.
	// this is the turn code.

	// this is the end of the turn, pass to next player.
	if ( ++active_player == players.end() )
		active_player = players.begin();
}

sf::Packet& Game::operator <<(sf::Packet& packet, const Game& game)
{
	return packet << game.players;
}

sf::Packet& Game::operator >>(sf::Packet& packet, Game& game)
{

}
