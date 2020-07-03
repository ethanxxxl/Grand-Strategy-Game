#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <iostream>
#include <SFML/Network.hpp>


int main()
{
	std::cout << "connecting..." << std::endl;
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(sf::IpAddress::getLocalAddress(), 53000);
	if ( status != sf::Socket::Done )
	{
		
	}
	std::cout << "connected!\nSending data..." << std::endl;


	std::cout << "finished sending." << std::endl;

}
