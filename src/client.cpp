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


	bool exit = false;
	std::string command;

	while ( !exit )
	{
		sf::Packet p;
		std::cout << "> ";

		std::cin >> std::ws;
		std::getline(std::cin, m1.u_console_print.message);
		p << m1;

		sf::Socket::Status result;
		do
		{
			result = socket.send(p);
		} while ( result != sf::Socket::Done );
		
		Message::ServerMessage sm;
		p.clear();

		do
		{
			result = socket.receive(p);
		} while ( result != sf::Socket::Done);

		p >> sm;

		std::cout << sm.u_status_report.message << std::endl;
	}

	std::cout << "finished sending." << std::endl;
}
