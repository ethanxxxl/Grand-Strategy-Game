#include "CONSTANTS.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <UITools.h>
#include <memory>
#include <iostream>

UITools::UITools(sf::RenderWindow* window, sf::View* view)
{
	this->window = window;
	this->view = view;
	enabled = true;
}

void UITools::set_active_tool(Tools tool)
{
	switch ( tool )
	{
		case Pan:
			{
				active_tool = std::make_unique<struct Pan>(this);
				break;
			}
		case Interact:
			{
				active_tool = std::make_unique<struct Interact>(this);
				break;
			}
		default:
			// nothing to do
			break;
	}
}

void UITools::event_callback(sf::Event event)
{
	// TODO look for certain key presses, then switch the active tool based on the key presss.
	if ( event.type == sf::Event::KeyPressed )
	{
		if ( event.key.code == sf::Keyboard::I )
			set_active_tool(Interact);
		else if ( event.key.code == sf::Keyboard::P )
			set_active_tool(Pan);
	}

	active_tool->function(event);
}

/* PAN TOOL
 */
void UITools::Pan::function(sf::Event event)
{
	if ( event.type == sf::Event::MouseWheelScrolled )
	{
		if (event.mouseWheelScroll.delta == 1)
			parent->view->zoom(0.5);
		else
			parent->view->zoom(1.5);

		parent->window->setView(*parent->view);
	}

	else if ( event.type == sf::Event::MouseMoved )
	{
		if ( sf::Mouse::isButtonPressed(sf::Mouse::Left) )
		{
			// you need to find where the mouse is in the game space, and move the view the same amount the
			// mouse moves.
			sf::Vector2i pixelPos = sf::Mouse::getPosition(*parent->window);
			sf::Vector2f new_mouse_pos = parent->window->mapPixelToCoords(pixelPos);
			
			parent->view->move(mouse_pos-new_mouse_pos);
			parent->window->setView(*parent->view);
		}
	}
	else if ( event.type == sf::Event::MouseButtonPressed )
	{
		sf::Vector2i pixelPos = sf::Mouse::getPosition(*parent->window);
		mouse_pos = parent->window->mapPixelToCoords(pixelPos);
	}
}


/* INTERACT TOOL
 */
UITools::Interact::Interact(UITools* parent) : Tool(parent)
{
	highlighted_tile = sf::RectangleShape(sf::Vector2f(CONSTANTS::tile_size, CONSTANTS::tile_size));
	highlighted_tile.setFillColor(sf::Color::White);
}

void UITools::Interact::function(sf::Event event)
{
	// when you hover over a tile, put a yellow square over top of it.
	// when the player clicks, and there is a unit on that tile, the tile will start blinking
	// when the player clicks another tile, then the unit will be moved to the new tile.

	// tool is selected
	// the player can select a tile
	// the player can select another tile
	// the unit is moved to the new tile
	
	// get the mouse position on the map
	sf::Vector2i pixelPos = sf::Mouse::getPosition(*parent->window);
	mouse_pos = parent->window->mapPixelToCoords(pixelPos);
	highlighted_tile.setPosition(mouse_pos);
}

void UITools::Interact::tool_draw()
{
	parent->window->draw(highlighted_tile);
}

void UITools::draw()
{
	active_tool->tool_draw();
}
