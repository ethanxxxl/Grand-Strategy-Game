#include <GameCore/Player.h>
#include <GameCore/World.h>
#include <string>

namespace GameCore
{
	Player::Player(std::string username)
	{
		this->username = username;
	}

	std::string Player::get_username(void)
	{
		return username;
	}
}