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

	sf::Packet p;
	client.receive(p);
	
	Message::ClientMessage m;
	p >> m;

	std::cout << m.m_username << " says: " << m.cp.message << std::endl;

	// use client to communicate with the connected server,
	// and continue to accept new connections with the listener
	std::vector<char> buf(100);
	std::size_t recieved;

	strcpy(buf.data(), "Hello there");
	std::cout << "result: " << std::string(buf.begin(), buf.end()) << std::endl;
	
	while ( true )
	{
		buf.clear();
		buf.resize(100);
		if ( client.receive(buf.data(), buf.capacity(), recieved) != sf::Socket::Done )
			std::cout << "failed" << std::endl;
		
		auto zero = {0};
		std::string command = {buf.begin(), std::ranges::find_first_of(buf, zero)};
		std::cout << command << std::endl;

		if ( command <=> "test" == 0)
		{
			const std::string t = "I hear you loud and clear\n";
			client.send(t.c_str(), t.length());
		}
		else
		{
			const std::string t = "unrecognized command\n";
			client.send(t.c_str(), t.length());
		}
	}

	client.disconnect();
}
