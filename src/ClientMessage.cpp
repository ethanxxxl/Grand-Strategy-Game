#include <ClientMessage.h>

sf::Packet& operator>>(sf::Packet& p, Message::ClientMessage& m)
{
	// ? for some reason, I need to use an intermediate variable for the enum class
	uint16_t cmd2;
	p >> m.m_playerID >> m.m_username >> cmd2;

	m.m_command = (Message::commands_t)cmd2;

	using namespace Message;
	switch ( m.m_command )
	{
		case commands_t::NONE:
			break;
		case commands_t::CONSOLE_PRINT:
			char buf[120];
			p >> buf;
			m.cp.message = buf;
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

sf::Packet& operator<<(sf::Packet& p, const Message::ClientMessage& m)
{
	// put in all the simple stuff
	p << m.m_playerID << m.m_username << (uint16_t)m.m_command;

	using namespace Message;
	switch ( m.m_command )
	{
		case commands_t::NONE:
			break;
		case commands_t::CONSOLE_PRINT:
			return p << m.cp.message;
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