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

#include <EventHandler.h>

// TODO change this to work with the new event handling system

// the way this class works, is that you set the window, and the current active tool.
// then, when you do you event handling, just stick use_tools() in with the event checking,
// it will use the proper tool for you.
//
// you do not need to make an object for this.
class UITools : public EventFunction
{
public:
	enum Tools { Pan, Interact };

private:
	struct Tool
	{
		UITools* parent;
		Tool(UITools* parent) : parent(parent) {};
		
		virtual void function(sf::Event event) = 0;
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
		sf::Vector2f mouse_pos;
		sf::RectangleShape highlighted_tile;

		void function(sf::Event event) override;
		Interact(UITools* parent);
		void tool_draw() override;
	};

	std::unique_ptr<Tool> active_tool;

public:
	sf::RenderWindow* window;
	sf::View* view;

	UITools(sf::RenderWindow* window, sf::View* view);

	void set_active_tool(Tools tool);
	void event_callback(sf::Event event) override;

	// draws UI tool elements
	void draw();
};


#endif
