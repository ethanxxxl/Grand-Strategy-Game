#include "Company.h"
#include <Player.h>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

Player::Player(std::string username)
{
	this->username = username;

	companies = std::vector<Company>();
	companies.push_back(Company(sf::Vector2i(3, 3)));
}

void Player::draw(sf::RenderTarget& target)
{
	for ( auto c = companies.begin(); c != companies.end(); ++c )
	{
		c->draw(target, color);
	}
}
