#include "Company.h"
#include <Player.h>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

std::vector<Player*> Player::players = std::vector<Player*>();

Player::Player(std::string username)
{
	player_id = players.size();
	players.push_back(this);
	
	this->username = username;

	companies = std::vector<Company>();
	companies.push_back(Company(player_id, sf::Vector2i(3, 3)));
}

Player::~Player()
{
	// remove this player from the list
	players.erase(players.begin()+player_id);
}

void Player::draw(sf::RenderTarget& target)
{
	for ( auto c = companies.begin(); c != companies.end(); ++c )
	{
		c->draw(target, color);
	}
}

Player* Player::player_by_id(int id)
{
	return players[id];
}
