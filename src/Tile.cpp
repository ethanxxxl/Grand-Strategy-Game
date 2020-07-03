#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <Tile.h>

#include <SFML/Graphics.hpp>

void Tile::draw(sf::RenderTarget &target, int x, int y)
{
	// set the size and location of the tile
	sf::RectangleShape tile_shape(sf::Vector2f(display_size, display_size));
	tile_shape.setPosition(x*display_size, y*display_size);
	tile_shape.setOutlineColor(sf::Color::White);

	// set the internal color of the tile.
	if ( terrain == WATER )
		tile_shape.setFillColor(sf::Color::Blue);
	else if ( terrain == LAND )
		tile_shape.setFillColor(sf::Color(0x008f1fff));
	else if ( terrain == MOUNTAIN )
		tile_shape.setFillColor(sf::Color::White);

	target.draw(tile_shape);
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
