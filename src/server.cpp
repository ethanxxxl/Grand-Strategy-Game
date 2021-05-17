#include <ClientMessage.h>
#include <ServerMessage.h>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <algorithm>
#include <array>
#include <cstring>
#include <iostream>
#include <memory>
#include <ranges>

int main()
{
	// create a game, set up players, wait for connection
	// client connects to the server as a player.
	// server sends client game data
    std::cout << "waiting for a connection..." << std::endl;
	// bind the listener to a port
	sf::TcpListener listener;
	if (listener.listen(53000) != sf::Socket::Done)
	{
		// error
	}


	// accept a new connection
	sf::TcpSocket client;
	if ( listener.accept(client) != sf::Socket::Done )
	{
		// errror
	}

    std::cout << "recieved a connection\nrecieving data..." << std::endl;

	while ( true )
	{
		sf::Packet p;
		Message::ClientMessage m;
		
		if ( client.receive(p) != sf::Socket::Done )
			std::cout << "failed" << std::endl;
		
		p >> m;
		std::cout << m.u_console_print.message << std::endl;

		p.clear();
		Message::ServerMessage sm;
		sm.m_msg_type =	Message::msgtype_t::STATUS_REPORT;

		if ( m.u_console_print.message <=> "test" == 0)
		{
			sm.u_status_report.success = true;
			sm.u_status_report.message = "I read you loud and clear";
		}
		else
		{
			sm.u_status_report.success = false;
			sm.u_status_report.message = "unrecognized command: " + m.u_console_print.message;
		}

		p << sm;
		client.send(p);
	}

	client.disconnect();
}
