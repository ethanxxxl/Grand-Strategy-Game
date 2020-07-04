#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <vector>
#include <Tile.h>
#include <cstdint>

class World
{
private:
	std::vector<std::vector<Tile>> world_data;

	sf::VertexArray tile_map;
	sf::VertexArray grid_map;

public:
	World(int size_x, int size_y);
	void draw(sf::RenderTarget &target);
	
};

#endif
