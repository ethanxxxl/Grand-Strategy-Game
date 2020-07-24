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
	// fill in window and view details
	this->window = window;
	this->view = view;
	enabled = true;  // make sure the event is enabled
}

void UITools::set_active_tool(Tools tool)
{
	// creates a new tool object when the tool is switched.
	//  if this ever causes problems, tool objects can be created in the constructor
	//  and enabled/disabled when switching tools.
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
	// Manage switching of tools based on player input
	if ( event.type == sf::Event::KeyPressed )
	{
		if ( event.key.code == sf::Keyboard::I )
			set_active_tool(Interact);
		else if ( event.key.code == sf::Keyboard::P )
			set_active_tool(Pan);
	}

	// call the active tool function (isn't inheritance great!?)
	active_tool->function(event);
}

/* PAN TOOL
 */
void UITools::Pan::function(sf::Event event)
{
	// Zoom handling
	if ( event.type == sf::Event::MouseWheelScrolled )
	{
		if (event.mouseWheelScroll.delta == 1)
			parent->view->zoom(0.5);
		else
			parent->view->zoom(1.5);

		parent->window->setView(*parent->view);
	}

	// Pan handling
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
		// I forget what exactly this stuff does, but I think it is important.
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
	// TODO make this actually work.
	// the player needs to be able to click on a tile, in order to select it,
	// then the player needs to be able to click another tile, and have the units
	// on the original tile move to the new one.
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
