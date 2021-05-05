#include <GameCore/Game.h>
#include <GameCore/Player.h>
#include <time.h>
#include <fstream>
#include <vector>

Game::Game(std::vector<Player> players, int world_size)
{
	srand(time(NULL));
	// generate a world
	world = World { world_size, rand() };

	// set players
	this->players = players;
	active_player = players.begin();
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
				// just return from the function, they cannot make a move.
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