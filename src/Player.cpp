#include "Company.h"
#include "World.h"
#include <Player.h>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>

Player::Player(std::shared_ptr<World> world, std::string username)
{
	this->username = username;
	this->world = world;

	// initialize the company list
	companies = std::vector<std::unique_ptr<Company>>();
}

void Player::new_company(int size, sf::Vector2i pos)
{
	// add a new company to the list
	companies.push_back(std::make_unique<Company>(size, pos));
}

void Player::draw(sf::RenderTarget& target)
{
	for ( auto c = companies.begin(); c != companies.end(); ++c )
	{
		(**c).draw(target, color);
	}
}
