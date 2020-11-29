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
	sf::RenderWindow window;
	sf::View view;

	// map constants
	const float tile_size = 10.0f;
	sf::VertexArray tile_map;
	sf::VertexArray grid_map;


public:
	GraphicsManager(Game& game, int win_width, int win_height);
	
	// TODO temporary just so things work with the UI
	sf::RenderWindow* get_window();
	sf::View* get_view();

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
