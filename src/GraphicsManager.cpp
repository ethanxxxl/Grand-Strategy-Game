#include <GraphicsManager.h>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

GraphicsManager::GraphicsManager(Game& game, int win_width, int win_height) : game(game)
{
	this->game = game;

	// create a window to draw in
	window.create(sf::VideoMode(win_width, win_height), "SFML works!");
	// define a viewport
	view = sf::View(sf::FloatRect(0,0,win_width,win_height));
	// and activate it
	window.setView(view);


	/* Set up map render stuff
	 */
	// Generate vertex array of the map to be rendered.
	tile_map = sf::VertexArray(sf::Quads);

	int size = game.get_world_size();
	// creates a bunch of colored squares.
	for ( auto x = 0; x != size; ++x )
	{
		for ( auto y = 0; y != size; ++y )
		{
			auto index = sf::Vector2f(y, x)*tile_size;
			auto offset = tile_size;

			tile_map.append(sf::Vertex(sf::Vector2f(index.x, index.y), \
							game.get_tile_at(x,y).draw_color()));						// top left
			tile_map.append(sf::Vertex(sf::Vector2f(index.x+offset, index.y), \
							game.get_tile_at(x,y).draw_color())); 						// top right
			tile_map.append(sf::Vertex(sf::Vector2f(index.x+offset, index.y+offset), \
							game.get_tile_at(x,y).draw_color())); 						// bottom right
			tile_map.append(sf::Vertex(sf::Vector2f(index.x, index.y+offset), \
							game.get_tile_at(x,y).draw_color())); 						// bottom left
		}
	}

	// create the grid lines for the map.
	grid_map = sf::VertexArray(sf::LineStrip);
	// go up and down
	for ( int y = 0; y < size; y+=2 )
	{
		float map_beg = 0;
		float map_end = size*tile_size;
		float cur_y = y*CONSTANTS::tile_size;
		grid_map.append(sf::Vertex(sf::Vector2f(map_beg, cur_y), sf::Color::Black));
		grid_map.append(sf::Vertex(sf::Vector2f(map_end, cur_y), sf::Color::Black));
		grid_map.append(sf::Vertex(sf::Vector2f(map_end, cur_y+CONSTANTS::tile_size), sf::Color::Black));
		grid_map.append(sf::Vertex(sf::Vector2f(map_beg, cur_y+CONSTANTS::tile_size), sf::Color::Black));
	}

	// Go across
	for ( int x = 0; x < size; x+=2 )
	{
		float map_top = 0;
		float map_bot = size*CONSTANTS::tile_size;
		float cur_x = x*CONSTANTS::tile_size;

		grid_map.append(sf::Vertex(sf::Vector2f(cur_x, map_top), sf::Color::Black));
		grid_map.append(sf::Vertex(sf::Vector2f(cur_x, map_bot), sf::Color::Black));
		grid_map.append(sf::Vertex(sf::Vector2f(cur_x+CONSTANTS::tile_size, map_bot), sf::Color::Black));
		grid_map.append(sf::Vertex(sf::Vector2f(cur_x+CONSTANTS::tile_size, map_top), sf::Color::Black));
	}
}

sf::RenderWindow* GraphicsManager::get_window()
{
	return &window;
}

sf::View* GraphicsManager::get_view()
{
	return &view;
}


void GraphicsManager::draw_all()
{
	draw_map();
	draw_entities();
	draw_effects();
	draw_UI();
}

void GraphicsManager::draw_map()
{
	window.draw(tile_map);
	window.draw(grid_map);
}

void GraphicsManager::draw_entities()
{
	for ( auto e = entities.begin(); e != entities.end(); e++ )
	{
		(**e).draw();
	}
}

void GraphicsManager::draw_effects()
{

}

void GraphicsManager::draw_UI()
{

}

void GraphicsManager::draw_company(Company& c)
{
	static const int display_radius = 3;

	sf::CircleShape dot(display_radius);
	// use the player color
	dot.setFillColor(c.player.get_color());

	// vector2i isn't implicitly converted to vector2f
	sf::Vector2f pos = sf::Vector2f(tile_size*(c.get_position().x+0.5f)-display_radius, tile_size*(c.get_position().y+0.5f)-display_radius);
	dot.setPosition(pos);
	window.draw(dot);
}
