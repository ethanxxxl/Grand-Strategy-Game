#ifndef CLIENTMESSAGE_H
#define CLIENTMESSAGE_H

#include <SFML/Network.hpp>
#include <string>

namespace Message
{
	// commands which can be sent to the server.
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
		ConsolePrint() : message() {};
		~ConsolePrint() {};
		// if you end up using this a lot, you could add more
		// options.
		std::string message;
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

	/**
	 * ClientMessage
	 *  this structure defines a message sent from a client program. the client will
	 *  be sending commands to the server, therefore one of the fields (m_command) 
	 *  defines the command which is being sent to the server.
	 * 
	 *  Additionally, there is a union which contains data specific to the command to be
	 *  sent to the server.
	 */
	struct ClientMessage
	{
		ClientMessage() : u_console_print() {};
		~ClientMessage() {};
		uint32_t m_playerID;
		std::string m_username;

		commands_t m_command;

		union
		{
			ConsolePrint u_console_print;
			SendChat u_send_chat;
			GetMoves u_get_moves;
			MoveUnit u_move_unit;
			GetInfo u_get_info;
		};
	};
}

/** operator overloads for each union member */
sf::Packet& operator<<(sf::Packet& p, const Message::ClientMessage& h);
sf::Packet& operator>>(sf::Packet& p, Message::ClientMessage& h);

#endif