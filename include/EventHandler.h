#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include <memory>
#include <vector>
#include <functional>


/* SYNOPSIS
 * EventFunction - contains a callback function that is called when the specified
 * event occures.
 *
 * event: the event associated with the callback
 *
 * enabled: if true, then the callback will be called. if false, the callback
 *   won't be called
 *
 * event_callback(): a pure virtual function that must be overwritten
 *
 * USAGE
 * a new child class should be created for each type of operation. these child classes
 *  can hold the data that the callback needs to operate on. 
 *
 * TODO add a type of 'event' that gets called every frame
 */
class EventFunction
{
public:
	const sf::Event::EventType event;
	bool enabled;

	virtual void event_callback() = 0;

	EventFunction(sf::Event::EventType event) : event(event)
	{
		enabled = true;
	}
};

/* SYNOPSIS
 * events: this is the master list of all events. It uses shared pointers to various
 *  event_function children
 *
 * window: this is the window that the event handler is detecting events on
 *
 * handle_events(): this function handles all of the events that are in the events vector
 *
 * USAGE
 * a new event handler should be made for every window. push an event function onto the vector
 *  to have it be called at its event.
 */
class EventHandler
{
private:
	sf::Window* window;

public:
	EventHandler(sf::Window* window);

	std::vector<std::shared_ptr<EventFunction>> events;
	~EventHandler();

	void handle_events();
};


/* Default Events
 */
class EventQuit : public EventFunction
{
public:
	sf::Window* window;
	void event_callback();

	// set the eventtype to closed
	EventQuit(sf::Window* window) : EventFunction(sf::Event::Closed) 
	{
		this->window = window;
	}
};

#endif
