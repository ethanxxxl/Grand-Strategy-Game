#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

#include <Game.h>
#include <Entity.h>
#include <vector>
#include <SFML/Graphics.hpp>

class GraphicsManager;

#include <Company.h>

class GraphicsManager
{
private:
	Game& game;
	std::vector<Entity*> entities; // entities to draw

	// you may want to include a sprite sheet or something in here
	// for textures
	
	sf::RenderWindow& window; // this is a reference because an sf::window does more than graphics
	sf::View view;

	// map constants
	const float tile_size = 10.0f;
	sf::VertexArray tile_map;
	sf::VertexArray grid_map;


public:
	GraphicsManager(sf::RenderWindow& window, Game& game, int win_width, int win_height);
	
	sf::RenderWindow& get_window(); // TODO this will be deleted soon!
	sf::View& get_view();

	void draw_all();

	// Generic draw functions
	void draw_map();
	void draw_entities();
	void draw_effects();
	void draw_UI();

	// specific draw functions
	void draw_company(Company& c);
};

#endif
