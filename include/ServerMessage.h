#ifndef SERVERMESSAGE_H
#define SERVERMESSAGE_H

#include <ClientMessage.h> /*I typically don't like mix headers up like this, but I think it is waranted in this case.*/
#include <SFML/Network.hpp>
#include <string>

namespace Message
{
	enum class msgtype_t : uint16_t
	{
		NONE,
		STATUS_REPORT
	};


	struct StatusReport
	{
		StatusReport() : message() {};
		~StatusReport() {};

		//? do you want to add a "job number" so that the client knows exactly what
		//?  command the message is referring to? if the need arises, this should be
		//?  added.
		bool success;
		std::string message;
	};

	/**
	 * ServerMessage
	 *  this structure is used to send/recieve messages from the server. The message
	 *  type signals to the client what type of message it is recieving. Notice that
	 *  this uses a union, so only one message type can be used at once.
	 */
	struct ServerMessage
	{
		ServerMessage() : u_status_report() {};
		~ServerMessage() {};
		msgtype_t m_msg_type;

		union
		{
			StatusReport u_status_report;
		};
	};

}

// extracts servermessage data from the packet.
sf::Packet& operator>>(sf::Packet& p, Message::ServerMessage& h);
sf::Packet& operator<<(sf::Packet& p, const Message::ServerMessage& h);
#endif