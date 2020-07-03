#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <Company.h>
#include <noise/module/terrace.h>

class Tile
{
private:
	const static int display_size = 10;


public:
	enum Terrain_t { LAND, WATER, MOUNTAIN};
	Terrain_t terrain;

	double altitude;

	Tile();
	Tile(double altitude);
	Tile(Terrain_t terrain);


	// pointer to the company that is on this tile
	std::shared_ptr<Company> company;

	void draw(sf::RenderTarget &target, int x, int y);
};

#endif
