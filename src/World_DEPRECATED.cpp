#include "Tile_DEPRECATED.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <World_DEPRECATED.h>
#include <cstddef>
#include <noise/module/perlin.h>
#include <vector>
#include <noise/noise.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <CONSTANTS.h>

World::World(int size_x, int size_y)
{
	this->size_x = size_x;
	this->size_y = size_y;

	// generate a world
	noise::module::Perlin noise_module;
	srand(time(NULL));
	noise_module.SetSeed(rand());

	// create a new vector
	world_data = std::vector<std::vector<Tile>>();
	// allocate enough space for all the tiles, in the y direcetion
	world_data.reserve(size_x);
	for ( int x = 0; x < size_x; ++x )
	{
		// allocate space for the actual tiles, in the x direction
		world_data.push_back(std::vector<Tile>());
		world_data[x].reserve(size_y);
		for ( int y = 0; y < size_y; ++y )
		{
			world_data[x].push_back(Tile(sf::Vector2i(x, y), noise_module.GetValue(x*0.1+1,y*0.1+1,1.0f)));
		}
	}

	// Generate vertex array of the map to be rendered.
	tile_map = sf::VertexArray(sf::Quads);

	// creates a bunch of colored squares.
	for ( auto x = world_data.begin(); x != world_data.end(); ++x )
	{
		for ( auto y = x->begin(); y != x->end(); ++y )
		{
			auto index = sf::Vector2f(y->get_pos().x, y->get_pos().y)*CONSTANTS::tile_size;
			auto offset = CONSTANTS::tile_size;

			tile_map.append(sf::Vertex(sf::Vector2f(index.x, index.y), y->draw_color())); // top left
			tile_map.append(sf::Vertex(sf::Vector2f(index.x+offset, index.y), y->draw_color())); // top right
			tile_map.append(sf::Vertex(sf::Vector2f(index.x+offset, index.y+offset), y->draw_color())); // bottom right
			tile_map.append(sf::Vertex(sf::Vector2f(index.x, index.y+offset), y->draw_color())); // bottom left
		}
	}

	// create the grid lines for the map.
	grid_map = sf::VertexArray(sf::LineStrip);
	// go up and down
	for ( int y = 0; y < size_y; y+=2 )
	{
		float map_beg = 0;
		float map_end = size_x*CONSTANTS::tile_size;
		float cur_y = y*CONSTANTS::tile_size;
		grid_map.append(sf::Vertex(sf::Vector2f(map_beg, cur_y), sf::Color::Black));
		grid_map.append(sf::Vertex(sf::Vector2f(map_end, cur_y), sf::Color::Black));
		grid_map.append(sf::Vertex(sf::Vector2f(map_end, cur_y+CONSTANTS::tile_size), sf::Color::Black));
		grid_map.append(sf::Vertex(sf::Vector2f(map_beg, cur_y+CONSTANTS::tile_size), sf::Color::Black));
	}

	// Go across
	for ( int x = 0; x < size_x; x+=2 )
	{
		float map_top = 0;
		float map_bot = size_y*CONSTANTS::tile_size;
		float cur_x = x*CONSTANTS::tile_size;

		grid_map.append(sf::Vertex(sf::Vector2f(cur_x, map_top), sf::Color::Black));
		grid_map.append(sf::Vertex(sf::Vector2f(cur_x, map_bot), sf::Color::Black));
		grid_map.append(sf::Vertex(sf::Vector2f(cur_x+CONSTANTS::tile_size, map_bot), sf::Color::Black));
		grid_map.append(sf::Vertex(sf::Vector2f(cur_x+CONSTANTS::tile_size, map_top), sf::Color::Black));
	}
}

void World::draw(sf::RenderTarget &target)
{
	target.draw(tile_map);
	target.draw(grid_map);
}

Tile* World::at(int x, int y)
{
	return &(world_data[x][y]);
}

Tile* World::at(sf::Vector2i pos)
{
	return &(world_data[pos.x][pos.y]);
}

Tile* World::at(sf::Vector2f pos)
{
	return &(world_data[floor(pos.x)][floor(pos.y)]);
}

sf::Vector2i World::get_size()
{
	return sf::Vector2i(size_x, size_y);
}