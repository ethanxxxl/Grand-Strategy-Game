#include "Tile.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <World.h>
#include <cstddef>
#include <noise/module/perlin.h>
#include <vector>
#include <noise/noise.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <CONSTANTS.h>

World::World(int size)
{
	this->size = size;

	// generate a world
	noise::module::Perlin noise_module;
	srand(time(NULL));
	noise_module.SetSeed(rand());

	// create a new vector
	world_data = std::vector<std::vector<Tile>>();
	// allocate enough space for all the tiles, in the y direcetion
	world_data.reserve(size);
	for ( int x = 0; x < size; ++x )
	{
		// allocate space for the actual tiles, in the x direction
		world_data.push_back(std::vector<Tile>());
		world_data[x].reserve(size);
		for ( int y = 0; y < size; ++y )
		{
			world_data[x].push_back(Tile(sf::Vector2i(x, y), noise_module.GetValue(x*0.1+1,y*0.1+1,1.0f)));
		}
	}
}

Tile& World::at(int x, int y)
{
	return (world_data[x][y]);
}

Tile& World::at(sf::Vector2i pos)
{
	return (world_data[pos.x][pos.y]);
}

Tile& World::at(sf::Vector2f pos)
{
	return (world_data[floor(pos.x)][floor(pos.y)]);
}

sf::Vector2i World::get_size()
{
	return sf::Vector2i(size, size);
}
