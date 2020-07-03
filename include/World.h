#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics/RenderTarget.hpp>
#include <vector>
#include <Tile.h>
#include <cstdint>

class World
{
private:
	std::vector<std::vector<Tile>> world_data;

public:
	World(int size_x, int size_y);
	void draw(sf::RenderTarget &target);
	
};

#endif
