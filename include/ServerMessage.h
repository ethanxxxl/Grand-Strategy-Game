#ifndef SERVERMESSAGE_H
#define SERVERMESSAGE_H

#include <ClientMessage.h> /*I typically don't like mix headers up like this, but I think it is waranted in this case.*/
#include <SFML/Network.hpp>
#include <string>

struct StatusReport
{
	//? do you want to add a "job number" so that the client knows exactly what
	//? command the message is referring to? if the need arises, this should be
	//? added.
	ClientMessage::commands_t client_command;
	bool success;
	std::string message;
};

struct ServerMessage;
sf::Packet& operator<<(sf::Packet& p, const ServerMessage& h);

sf::Packet& operator<<(sf::Packet& p, const StatusReport& h);

/**
 * --ServerMessage--
 * this is a message that is sent from the server to the client.
 */
struct ServerMessage
{
	enum class msgclass_t : uint16_t
	{
		STATUS_REPORT
	} msgclass;

	union MesssageBody
	{
		StatusReport status_report;
	} message_body;
};

#endif