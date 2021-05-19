#ifndef COMMANDS_H
#define COMMANDS_H

#include <cstdint>

namespace Message
{
	/**
	 * \brief Commands which a client can send to a server
	 * 
	 * This enumeration defines all of the commands which can be sent from a client to a server.
	 *  Messages from both the client and the server use this enumeration to define the type of message
	 *  being sent
	 */
	enum class commands_t: uint16_t
	{
		CONSOLE_PRINT, 		///< Print a message on the server console
		GET_WORLD,			///< Get a copy of the world
		GET_INFO,			///< Get info on a specific GameObject
		GET_MOVES,			///< Get a list of all the valid moves for a unit
		MOVE_UNIT, 			///< Attempt to move the specified unit
		SEND_CHAT			///< Send a chat
	};
}

#endif