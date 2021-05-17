#include <ClientMessage.h>
#include <ServerMessage.h>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>


int main()
{
	std::cout << "connecting..." << std::endl;
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(sf::IpAddress::getLocalAddress(), 53000);
	if ( status != sf::Socket::Done )
	{
		
	}
	std::cout << "connected!\n" << std::endl;

	Message::ClientMessage m1;
	m1.m_command = Message::commands_t::CONSOLE_PRINT;
	m1.m_username = "ethan";
	m1.cp.message = "hello there";

	sf::Packet p;

	p << m1;
	socket.send(p);

	bool exit = false;
	std::string command;

	std::vector<char> buf(100);
	std::size_t recieved;

	while ( !exit )
	{
		std::cout << "> ";

		std::cin >> std::ws;
		std::getline(std::cin, command);

		command.append("\0");

		sf::Socket::Status result;
		do
		{
			result = socket.send((void*)command.c_str(), command.length());
		} while ( result != sf::Socket::Done );
		
		do
		{
			result = socket.receive(buf.data(), buf.capacity(), recieved);
		} while ( result != sf::Socket::Done);

		std::cout << buf.data() << std::endl;
	}

	std::cout << "finished sending." << std::endl;
}
