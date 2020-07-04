#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <string>
#include <Company.h>
#include <vector>

class Player
{
private:
	std::vector<Company> companies;

public:
	Player(std::string username);
	std::string username;
	sf::Color color = sf::Color::Black;

	void draw(sf::RenderTarget& target);
};

#endif
