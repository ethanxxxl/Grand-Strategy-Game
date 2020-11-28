#include "CONSTANTS.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <UITools.h>
#include <limits>
#include <memory>
#include <iostream>

UITools::UITools(sf::RenderWindow* window, sf::View* view, std::shared_ptr<World> world)
{
	// fill in window and view details
	this->window = window;
	this->view = view;
	this->world = world;
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
	hover_tile = sf::RectangleShape(sf::Vector2f(CONSTANTS::tile_size, CONSTANTS::tile_size));
	hover_tile.setFillColor(sf::Color::White);

	src_tile_gfx = sf::RectangleShape(sf::Vector2f(CONSTANTS::tile_size, CONSTANTS::tile_size));
	src_tile_gfx.setFillColor(sf::Color::Yellow);

	world = parent->world;
	state = select_src;
}

void UITools::Interact::function(sf::Event event)
{
	// find the mouse position
	sf::Vector2i pixelPos = sf::Mouse::getPosition(*parent->window);
	mouse_pos = parent->window->mapPixelToCoords(pixelPos);

	// find the coords for the tile the mouse is over
	auto hover_tile_coords = mouse_pos / CONSTANTS::tile_size;
	hover_tile_coords = sf::Vector2f(std::floor(hover_tile_coords.x), std::floor(hover_tile_coords.y));
	// tool state machine
	if ( sf::Mouse::isButtonPressed(sf::Mouse::Left) )
	{
	switch ( state )
		{
			// when in this state, the player needs to select the first tile
			case select_src:
			{
				// bounds checking
				if ( ( hover_tile_coords.x >= 0 and hover_tile_coords.x < world->get_size().x ) and \
					 ( hover_tile_coords.y >= 0 and hover_tile_coords.y < world->get_size().y ) )
				{
					// grap pointer to the src tile
					src_tile = world->at(hover_tile_coords);
					
					// make sure there is a company on this tile
					if ( src_tile->company != NULL )
					{
						src_tile_gfx.setPosition(hover_tile_coords*CONSTANTS::tile_size);
						state = select_dest;
					}
				}

				break;
			}

			// when in this state, the player needs to select the second tile
			case select_dest:
			{
				// bounds checking
				if ( ( hover_tile_coords.x >= 0 and hover_tile_coords.x < world->get_size().x ) and \
					 ( hover_tile_coords.y >= 0 and hover_tile_coords.y < world->get_size().y ) )
				{
					// get a pointer the dest tile
					dest_tile = world->at(hover_tile_coords);
					if ( dest_tile == src_tile )
					{
						// if they are the same tile, don't try to move the company, and muck things up
						//  also prevents the dragging 'n' drop "feature"
						state = select_src;
					}
					else if ( dest_tile->company == NULL )
					{
						// there is not a company on the destination tile, so just move it there.
						src_tile->company->move(dest_tile);
						state = select_src;
					}
					// TODO implement fighting
				}

				break;
			}
		}
	}

	hover_tile.setPosition(hover_tile_coords*CONSTANTS::tile_size);
}

void UITools::Interact::tool_draw()
{
	parent->window->draw(hover_tile);

	if ( state == select_dest )
		parent->window->draw(src_tile_gfx);
}

void UITools::draw()
{
	active_tool->tool_draw();
}
