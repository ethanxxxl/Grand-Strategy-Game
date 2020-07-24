#include <EventHandler.h>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include <memory>
#include <iostream>


EventHandler::EventHandler(sf::Window* window)
{
	// save the reference to the window
	this->window = window;

	auto quit_event = std::make_shared<EventQuit>(window);
	events.push_back(quit_event);
}

EventHandler::~EventHandler()
{
	for ( auto i = events.begin(); i != events.end(); ++i )
	{
		i->reset();
	}
}

void EventHandler::handle_events()
{
	sf::Event event;
	// poll all of the events
	while (window->pollEvent(event))
	{
		for ( auto e = events.begin(); e != events.end(); ++e )
		{
			if ( (**e).enabled == true )
			{
				(**e).event_callback(event);
			}
		}

	}
}

void EventQuit::event_callback(sf::Event event)
{
	if ( event.type == sf::Event::Closed )
		window->close();
}
