#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <Company.h>
#include <noise/module/terrace.h>
#include <CONSTANTS.h>

class Tile
{
private:

public:
	enum Terrain_t { LAND, WATER, MOUNTAIN};
	Terrain_t terrain;

	double altitude;

	Tile();
	Tile(double altitude);
	Tile(Terrain_t terrain);

	sf::Color draw_color();
};

#endif
