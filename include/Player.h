#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics/Color.hpp>
#include <string>
#include <vector>

class Player;

/* SYNOPSIS
 * players represent people that play the game. This will hold their information, and
 * it can be referenced show who owns a particular entity.
 */
class Player
{
private:
	// these things don't need to change
	std::string username;
	sf::Color color;

public:
	/*
	 * Constructors
	 */
	Player(std::string username, sf::Color color);

	/*
	 * Methods
	 */
	sf::Color get_color();
	std::string get_username();
};

#endif
