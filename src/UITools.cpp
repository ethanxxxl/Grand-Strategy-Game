#include "CONSTANTS.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <UITools.h>
#include <memory>
#include <iostream>

UI_Tools::Tools		UI_Tools::active_tool;
sf::RenderWindow*	UI_Tools::window;
sf::View*			UI_Tools::view;
sf::Vector2f		UI_Tools::mouse_pos;

void UI_Tools::set_active_tool(Tools tool)
{
	active_tool = tool;
}

void UI_Tools::pan(sf::Event event)
{
	if ( event.type == sf::Event::MouseWheelScrolled )
	{
		if (event.mouseWheelScroll.delta == 1)
			view->zoom(0.5);
		else
			view->zoom(1.5);

		window->setView(*view);
	}

	else if ( event.type == sf::Event::MouseMoved )
	{
		if ( sf::Mouse::isButtonPressed(sf::Mouse::Left) )
		{
			// you need to find where the mouse is in the game space, and move the view the same amount the
			// mouse moves.
			sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
			sf::Vector2f new_mouse_pos = window->mapPixelToCoords(pixelPos);
			
			view->move(mouse_pos-new_mouse_pos);
			window->setView(*view);
		}
	}
	else if ( event.type == sf::Event::MouseButtonPressed )
	{
		sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
		mouse_pos = window->mapPixelToCoords(pixelPos);
	}
}

void UI_Tools::interract(sf::Event event)
{
	// when you hover over a tile, put a yellow square over top of it.
	// when the player clicks, and there is a unit on that tile, the tile will start blinking
	// when the player clicks another tile, then the unit will be moved to the new tile.
	
	// get the mouse position on the map
	sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
	mouse_pos = window->mapPixelToCoords(pixelPos);

	std::cout << mouse_pos.x << " " << mouse_pos.y << std::endl;

	sf::RectangleShape on_hover_square(sf::Vector2f(CONSTANTS::tile_size, CONSTANTS::tile_size));
	on_hover_square.setPosition(mouse_pos);

	window->draw(on_hover_square);
}

void UI_Tools::use_tools(sf::Event event)
{
	// TODO look for certain key presses, then switch the active tool based on the key presss.
	
	switch (active_tool)
	{
		case Pan_Map:
			{
				pan(event);
				break;
			}
		case Interract:
			{
				interract(event);
				break;
			}
		default:
			// nothing to do
			break;
	}
}
