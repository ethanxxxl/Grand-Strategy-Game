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
	sf::Color color = sf::Color::Black;

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
	Player(std::shared_ptr<World> world, std::string username);

	/*
	 * Methods
	 */
	void new_company(int size, sf::Vector2i pos);


	void draw(sf::RenderTarget& target);
};

#endif
