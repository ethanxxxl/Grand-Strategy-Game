#ifndef CLIENTMESSAGE_H
#define CLIENTMESSAGE_H

#include <SFML/Network.hpp>
#include <string>

namespace Message
{
	enum class commands_t: uint16_t
	{
		NONE,
		CONSOLE_PRINT,
		SEND_CHAT,
		GET_MOVES,
		MOVE_UNIT,
		GET_INFO
	};

	struct ConsolePrint
	{
		// if you end up using this a lot, you could add more
		// options.
		// pointer to null terminated message string;
		char* message;
	};

	struct SendChat
	{
	};

	struct GetMoves
	{
	};

	struct MoveUnit
	{
	};

	struct GetInfo
	{
	};

	struct ClientMessage
	{
		ClientMessage() : cp() {};
		uint32_t m_playerID;
		std::string m_username;

		commands_t m_command;

		union
		{
			ConsolePrint cp;
			SendChat sc;
			GetMoves gm;
			MoveUnit mu;
			GetInfo gi;
		};
	};
}

/** operator overloads for each union member */
sf::Packet& operator<<(sf::Packet& p, const Message::ClientMessage& h);
sf::Packet& operator>>(sf::Packet& p, Message::ClientMessage& h);

#endif