#include "Company.h"
#include "World.h"
#include <Player.h>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>

Player::Player(std::string username, sf::Color color)
{
	this->username = username;
	this->color = color;

	// initialize the company list
	companies = std::vector<std::unique_ptr<Company>>();
}

Player::Player(std::string username, sf::Color color, std::shared_ptr<World> world)
{
	Player(username, color);
	this->world = world;
}

void Player::add_company(int size, sf::Vector2i pos)
{
	// add a new company to the list
	companies.push_back(std::make_unique<Company>(this, pos, size));
}

sf::Color Player::get_color()
{
	return color;
}

std::string Player::get_username()
{
	return username;
}

void Player::draw(sf::RenderTarget& target)
{
	for ( auto c = companies.begin(); c != companies.end(); ++c )
	{
		(**c).draw(target, color);
	}
}
