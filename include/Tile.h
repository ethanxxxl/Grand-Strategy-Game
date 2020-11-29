#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <noise/module/terrace.h>
#include <CONSTANTS.h>

class Tile
{
private:
	// this is the position of the tile in the world array.
	sf::Vector2i pos;

public:
	enum Terrain_t { LAND, WATER, MOUNTAIN};
	Terrain_t terrain;

	double altitude;
	
	Tile(sf::Vector2i pos);
	Tile(sf::Vector2i pos, double altitude);
	Tile(sf::Vector2i pos, Terrain_t terrain);

	sf::Color draw_color();

	// returns position in list
	sf::Vector2i get_pos();
	// returns the coordinates of the center of
	// the  tile in world space
	sf::Vector2f get_spacial_coords();
};

#endif
