#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <cstdint>

class World;
#include <Tile_DEPRECATED.h>

class World
{
private:
	std::vector<std::vector<Tile>> world_data;

	int size_x;
	int size_y;

	sf::VertexArray tile_map;
	sf::VertexArray grid_map;

public:
	World(int size_x, int size_y);
	void draw(sf::RenderTarget &target);

	Tile* at(int x, int y);
	Tile* at(sf::Vector2i pos);
	// note that when using a float, the index will be rounded down with floor().
	Tile* at(sf::Vector2f pos);

	sf::Vector2i get_size();
};

#endif
