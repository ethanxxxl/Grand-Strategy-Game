#include "Company.h"
#include "World.h"
#include <Player.h>
#include <SFML/System/Vector2.hpp>
#include <memory>

Player::Player(std::string username, sf::Color color)
{
	this->username = username;
	this->color = color;
}

sf::Color Player::get_color()
{
	return color;
}

std::string Player::get_username()
{
	return username;
}
