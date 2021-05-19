#ifndef CLIENTMESSAGE_H
#define CLIENTMESSAGE_H

#include <Message/Commands.h>
#include <SFML/Network.hpp>
#include <string>

namespace Message
{
	/**
	 * \brief Defines a message sent from a client to a server.
	 * 
	 * Defines a message sent from a client program. There are multiple types of messages, which correspond
	 *  to the enumerators of `Message::commands_t`. Additionally, some messages have additional data which
	 *  needs to be sent. This data is referenced to by the anonymous union. See `Message::Server` for info about
	 *  the corresponding class for the server.
	 * 
	 * The insertion (<<) and extraction (>>) operators are overloaded to work with `sf::Packets` 
	 * 
	 * Note: when this message is recieved by the server, upon extraction from the packet, any command specific data
	 *  (ie. data which is located in the union) will be stored in new objects, which will be referenced by the members
	 *  of the active union member.
	 */
	struct Client
	{
		uint32_t m_playerID; 	///< unique ID of the player
		std::string m_username; ///< player username

		commands_t m_command; 	///< command to send to the server

		/// data associated with the CONSOLE_PRINT command
		struct ConsolePrint
		{
			// if you end up using this a lot, you could add more
			// options.
			// TODO make this a smart pointer
			std::string* message; ///< pointer to a message to send.
		};

		/**
		 * \brief contains specific data for a given `m_command`
		 * 
		 * If a command has additional data to send to the server, then it is included
		 *  in this union. Note that not all commands require additional data, and thus
		 *  do not have associated structures or entries in this union.
		 */
		union
		{
			ConsolePrint u_console_print;
		};
	};
}

/**
 * \brief extracts client message from a packet
 * 
 * This extraction operator overload takes the data from the packet, and puts it into
 *  a message structure. If the command required any specific data to be sent along,
 *  then a new object will be created, and the pointers in the associated structure will
 *  point to the new object.
 * 
 * @param p a packet that was recieved from a client
 * @param h an empty client message 
 */
sf::Packet& operator>>(sf::Packet& p, Message::Client& h);

/**
 * \brief inserts a client message into a packet
 * 
 * @param p a packet which will be sent to the server
 * @param h the client message to send
 */
sf::Packet& operator<<(sf::Packet& p, const Message::Client& h);

#endif