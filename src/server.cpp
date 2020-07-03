#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Network.hpp>
#include <SFML/Network/Socket.hpp>
#include <SFML/Network/TcpListener.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>

#include <Tile.h>
#include <array>
#include <UITools.h>
#include <World.h>

int main()
{
//    std::cout << "waiting for a connection..." << std::endl;
//	// bind the listener to a port
//	sf::TcpListener listener;
//	if (listener.listen(53000) != sf::Socket::Done)
//	{
//		// error
//	}
//
//
//	// accept a new connection
//	sf::TcpSocket client;
//	if ( listener.accept(client) != sf::Socket::Done )
//	{
//		// errror
//	}
//
//    std::cout << "recieved a connection\nrecieving data..." << std::endl;
//
//	// use client to communicate with the connected server,
//	// and continue to accept new connections with the listener
//	char buf[100];
//	std::size_t recieved;
//	if ( client.receive(buf, 100, recieved) != sf::Socket::Done )
//	{
//		// there was an error
//	}
//
//
//	std::cout << buf << std::endl;
//
//	client.disconnect();

	// GENERATE WORLD MAP
	const int WORLD_SIZE_X = 50;
	const int WORLD_SIZE_Y = 50;

	World the_world(WORLD_SIZE_X, WORLD_SIZE_Y);

	// create the window
	sf::RenderWindow window(sf::VideoMode(800, 400), "SFML works!");
	
	// define the viewport
	sf::View view(sf::FloatRect(200,200,300,200));
	// and activate it
	window.setView(view);


	// Configure UI tools
	UI_Tools::window = &window;
	UI_Tools::view = &view;

	UI_Tools::set_active_tool(UI_Tools::Pan_Map);

	while (window.isOpen())
	{
		window.clear(sf::Color::Black);

		// EVENT HANDLING
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if ( event.type == sf::Event::MouseWheelScrolled )
			{
				if (event.mouseWheelScroll.delta == 1)
					view.zoom(0.5);
				else
					view.zoom(1.5);

				window.setView(view);
			}

			UI_Tools::use_tools(event);

			
		}

		the_world.draw(window);

		window.display();

	}


  return 0;
	
}