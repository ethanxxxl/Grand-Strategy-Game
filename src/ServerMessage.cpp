#include <ServerMessage.h>

sf::Packet& operator>>(sf::Packet& p, Message::ServerMessage& m)
{
	// extract member data
	// ? for some reason, I need to use an intermediate variable for the enum class
	uint16_t msg;
	p >> msg;
	m.m_msg_type = (Message::msgtype_t)msg;

	// extract union data
	using namespace Message;
	switch ( m.m_msg_type )
	{
		case msgtype_t::NONE:
			break;
		case msgtype_t::STATUS_REPORT:
			return p >> m.u_status_report.success >> m.u_status_report.message;
	}
	return p;
}

sf::Packet& operator<<(sf::Packet& p, const Message::ServerMessage& m)
{
	// insert member data
	p << (uint16_t)m.m_msg_type;

	// insert union data
	using namespace Message;
	switch ( m.m_msg_type )
	{
		case msgtype_t::NONE:
			break;
		case msgtype_t::STATUS_REPORT:
			return p << m.u_status_report.success << m.u_status_report.message;
	}
	return p;
}