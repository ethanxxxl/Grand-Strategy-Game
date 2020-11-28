#ifndef UITOOLS_H
#define UITOOLS_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Window.hpp>
#include <string>
#include <memory>

#include <World.h>

#include <EventHandler.h>

/* SYNOPSIS
 * UITools: this is an EventFunction, it manages all player interaction with the game.
 *  currently, to start this, an object must be made, and it needs to be attached to the
 *  window and view that the game is in. The active tool can be changed in software or in
 *  game, with the mapped keys.
 *
 * draw(): this function needs to be called *after* the map draw commands in the main
 *  loop. This may change in the future.
 *
 * USAGE
 * As highlighted above, a UITools object needs to be made for every window the player is
 *  to interact with.
 * To add a new tool to the game, create a new sublass, derived from the Tool subclass, and
 *  fill in the required fields. Having each tool encapsulated in a separate class allows
 *  for more convenient operations such as drawing and event handling.
 */
class UITools : public EventFunction
{
public:
	enum Tools { Pan, Interact };

private:
	struct Tool
	{
		// reference to the original UITools object that created this instance
		UITools* parent;
		Tool(UITools* parent) : parent(parent) {};
		// this is what the tool does
		virtual void function(sf::Event event) = 0;

		// anything that the tool needs to draw should be done here. this is called every
		//  frame, while function is only called when there are events that need handled.
		virtual void tool_draw() = 0;
	};

	struct Pan : public Tool
	{
		sf::Vector2f mouse_pos;

		void function(sf::Event event) override;
		Pan(UITools* parent) : Tool(parent) {};
		void tool_draw() override {}
	};

	struct Interact : public Tool
	{
	private:
		enum State { select_src, select_dest } state;
		sf::Vector2f mouse_pos;
		sf::RectangleShape hover_tile;
		sf::RectangleShape src_tile_gfx;

		std::shared_ptr<World> world;

		Tile* src_tile;
		Tile* dest_tile;

	public:
		void function(sf::Event event) override;
		Interact(UITools* parent);
		void tool_draw() override;
	};

	std::unique_ptr<Tool> active_tool;

public:
	sf::RenderWindow* window;
	sf::View* view;

	std::shared_ptr<World> world;

	UITools(sf::RenderWindow* window, sf::View* view, std::shared_ptr<World> world);

	void set_active_tool(Tools tool);
	void event_callback(sf::Event event) override;

	// draws UI tool elements
	void draw();
};


#endif
