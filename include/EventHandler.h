#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <SFML/Window/Event.hpp>

#include <SFML/Window.hpp>
#include <memory>
#include <vector>
#include <functional>


/* SYNOPSIS
 * EventFunction - contains a callback function that will get called in the event handling
 *  process
 *
 * enabled: if true, then the callback will be called. if false, the callback
 *   won't be called
 *
 * event_callback(): a pure virtual function that must be overwritten
 *
 * USAGE
 * a new child class should be created for each type of operation. these child classes
 *  can hold the data that the callback needs to operate on. 
 */
class EventFunction
{
public:
	// all eventfunctions will likley need to access the window,
	//  since the events come from the window
	sf::Window& window;
	bool enabled;

	// simple constructor to initialize window
	EventFunction(sf::Window& window) : window(window) {};

	virtual void event_callback(sf::Event event) = 0;
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
	sf::Window& window;

public:
	EventHandler(sf::Window& window);

	std::vector<std::shared_ptr<EventFunction>> events;
	~EventHandler();

	void handle_events();
};


/* Default Events
 */
class EventQuit : public EventFunction
{
public:
	void event_callback(sf::Event event);

	// set the eventtype to closed
	EventQuit(sf::Window& window) : EventFunction(window)
	{
		enabled = true;
	}
};

#endif
