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

Tile::Tile(double altitude)
{
	if ( altitude > 0.85f )
		terrain = MOUNTAIN;
	else if ( altitude > -0.5f )
		terrain = LAND;
	else if ( altitude > -1.0f )
		terrain = WATER;

	this->altitude = altitude;
}

Tile::Tile(Terrain_t terrain)
{
	this->terrain = terrain;
}

Tile::Tile()
{
	terrain = LAND;
}
