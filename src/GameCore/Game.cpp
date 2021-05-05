#include <GameCore/Game.h>
#include <GameCore/Player.h>
#include <time.h>
#include <algorithm>
#include <fstream>
#include <vector>

Game::Game(std::vector<Player> players, int world_size)
{
	srand(time(NULL));
	// generate a world
	world = World { world_size, rand() };

	// set players
	this->m_players = players;
	active_player = players.begin();
}

void Game::play_turn(std::string username)
{
	for ( auto n = m_players.begin(); n != m_players.end(); ++n )
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
	if ( ++active_player == m_players.end() )
		active_player = m_players.begin();
}

std::vector<cube_coords_t> Game::get_valid_moves(int ID)
{
	/* -- FIND OBJECT -- 
	 */

	// lambda for easy checking of ID
	auto check_ID = [ID](GameObject* o) { return o->m_ID == ID; };

	// the objects we are looking through
	const std::vector<GameObject*> objs = GameObject::objects();

	// find the object, if it is not in the list, then return an empty set of valid moves.
	auto result = std::ranges::find_if(objs, check_ID);
	if ( result == objs.end() )
		return {};

	// get the valid moves and return them.
	return get_valid_moves(*result);
}

// TODO implement this!
std::vector<cube_coords_t> Game::get_valid_moves(GameObject* obj)
{
	return {};
}

bool Game::move_object(int ID)
{
	return 0;
}

bool Game::move_object(GameObject* obj)
{
	return 0;
}