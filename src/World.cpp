#include "Tile.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <World.h>
#include <noise/module/perlin.h>
#include <vector>
#include <noise/noise.h>
#include <iostream>

World::World(int size_x, int size_y)
{
	// generate a world
	noise::module::Perlin noise_module;

	// create a new vector
	world_data = std::vector<std::vector<Tile>>();
	// allocate enough space for all the tiles, in the y direcetion
	world_data.reserve(size_x);
	for ( int x = 0; x < size_x; x++ )
	{
		// allocate space for the actual tiles, in the x direction
		world_data.push_back(std::vector<Tile>());
		world_data[x].reserve(size_y);
		for ( int y = 0; y < size_y; y++ )
		{
			world_data[x].push_back(Tile(noise_module.GetValue(x*0.1+1,y*0.1+1,1.0f)));
		}
	}
}

void World::draw(sf::RenderTarget &target)
{
	for ( auto x = world_data.begin(); x != world_data.end(); ++x )
	{
		for ( auto y = x->begin(); y != x->end(); ++y )
		{
			y->draw(target, x-world_data.begin(), y- x->begin());
		}
	}
}
