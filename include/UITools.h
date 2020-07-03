#ifndef UITOOLS_H
#define UITOOLS_H

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Window.hpp>
#include <string>
#include <memory>

// the way this class works, is that you set the window, and the current active tool.
// then, when you do you event handling, just stick use_tools() in with the event checking,
// it will use the proper tool for you.
//
// you do not need to make an object for this.
class UI_Tools
{
public:
	enum Tools { Pan_Map, Interract };
private:
	static Tools active_tool;

	static void pan(sf::Event event);
	static sf::Vector2f mouse_pos;

	static void interract(sf::Event event);

public:
	static sf::RenderWindow* window;
	static sf::View* view;

	static void set_active_tool(Tools tool);
	static void use_tools(sf::Event event);
};

#endif
