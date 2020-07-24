#include "CONSTANTS.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <Tile.h>

#include <SFML/Graphics.hpp>

sf::Color Tile::draw_color()
{
	// return the proper color
	if ( terrain == WATER )
		return sf::Color::Blue;
	else if ( terrain == LAND )
		return sf::Color(0x008f1fff);
	else if ( terrain == MOUNTAIN )
		return sf::Color::White;

	return sf::Color::Black;
}

Tile::Tile(sf::Vector2i pos, double altitude)
{
	if ( altitude > 0.85f )
		terrain = MOUNTAIN;
	else if ( altitude > -0.5f )
		terrain = LAND;
	else if ( altitude > -1.0f )
		terrain = WATER;

	this->altitude = altitude;
	this->pos = pos;
}

Tile::Tile(sf::Vector2i pos, Terrain_t terrain)
{
	this->terrain = terrain;
	this->pos = pos;
}

Tile::Tile(sf::Vector2i pos)
{
	terrain = LAND;
	this->pos = pos;
}

sf::Vector2i Tile::get_pos()
{
	return pos;
}

sf::Vector2f Tile::get_world_coords()
{
	return sf::Vector2f(pos.x+CONSTANTS::tile_size/2, pos.y+CONSTANTS::tile_size/2);
}
