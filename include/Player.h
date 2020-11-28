#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <string>
#include <vector>

class Player;
#include <Company.h>
#include <World.h>

class Player
{
private:
	// these things don't need to change
	std::string username;
	sf::Color color;

public:
	/*
	 * Member Data
	 */
	std::shared_ptr<World> world;

	std::vector<std::unique_ptr<Company>> companies;
	// std::vector<std::unique_ptr<City>> cities;
	// std::vector<std::unique_ptr<Farm>> farms;
	// ...

	/*
	 * Constructors
	 */
	Player(std::string username, sf::Color color);
	Player(std::string username, sf::Color color, std::shared_ptr<World> world);

	/*
	 * Methods
	 */
	void add_company(int size, sf::Vector2i pos);
	sf::Color get_color();
	std::string get_username();

	void draw(sf::RenderTarget& target);
};

#endif
