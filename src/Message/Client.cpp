#include <Message/Client.h>
#include <SFML/Network.hpp>

sf::Packet& operator>>(sf::Packet& p, Message::Client& m)
{
	// extract member data from the packet
	uint16_t cmd;
	p >> m.m_playerID >> m.m_username >> cmd;
	m.m_command = (Message::commands_t)cmd;

	// extract union data from packet, then return the packet.
	using namespace Message;
	switch ( m.m_command )
	{
		case commands_t::CONSOLE_PRINT:
			return p >> m.u_console_print.message;
		case commands_t::GET_WORLD:
			return p;
		case commands_t::SEND_CHAT:
			break;
		case commands_t::GET_MOVES:
			break;
		case commands_t::MOVE_UNIT:
			break;
		case commands_t::GET_INFO:
			break;
	}
	return p;
}

sf::Packet& operator<<(sf::Packet& p, const Message::Client& m)
{
	// insert member data
	p << m.m_playerID << m.m_username << (uint16_t)m.m_command;

	// insert union data
	using namespace Message;
	switch ( m.m_command )
	{
		case commands_t::CONSOLE_PRINT:
			return p << m.u_console_print.message;
		case commands_t::GET_WORLD:
			return p;
		case commands_t::SEND_CHAT:
			break;
		case commands_t::GET_MOVES:
			break;
		case commands_t::MOVE_UNIT:
			break;
		case commands_t::GET_INFO:
			break;
	}
	return p;
}