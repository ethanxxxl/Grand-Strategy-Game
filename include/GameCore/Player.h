#ifndef PLAYER_H
#define PLAYER_H

#include <GameCore/GameObject.h>
#include <GameCore/Player.h>
#include <string>
#include <vector>

namespace GameCore
{
	/// describes a player
	class Player
	{
	private:
		std::string username; ///< players username, may not be unique
		int32_t ID;			  ///< ID which will be unique to every player

	public:
		//std::vector<GameObject&> objects;

		/// @param username every player must, at the very least have a username
		Player(std::string username);
		
		/// returns the username
		std::string get_username(void);
	};
}

#endif
