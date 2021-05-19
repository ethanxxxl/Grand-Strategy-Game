#ifndef SERVERMESSAGE_H
#define SERVERMESSAGE_H

#include <Message/Commands.h>
#include <GameCore/World.h>
#include <SFML/Network.hpp>
#include <string>

namespace Message
{
	/**
	 * \brief Defines a message sent by the server
	 * 
	 * This structure is used to send/recieve messages from the server. These messages are
	 *  sent in response to messages sent from the client (`Message::Client`). As such, it uses
	 *  the same enumeration, `Message::commands_t` to differentiate between the different types of messages
	 *  that it can send (a response will always have the same command type as the corresponding
	 *  client message). Like the client message struct, some responses will require additional data
	 *  to be sent back to the client. This additional data is located in the union.
	 * 
	 * Additionally, the inseration (<<) and extraction (>>) operators are overloaded to allow easy
	 *  use with `sf::Packet` types.
	 */
	struct Server
	{
		Server() {};
		~Server() {};

		commands_t m_command;	///< The command that the server is responding to

		bool success;			///< True if whatever the server did was successful

		/// struct containing data pertaining to the `GET_WORLD` command
		struct GetWorld
		{
			/**
			 * \brief Pointer to the world object
			 * If the message has been sent, then this should point to an existing world object.
			 *  if the message was recieved, then this will point to a new world object
			 */
			GameCore::World* world;
		};

		union
		{
			GetWorld u_send_world;
		};
	};

}

/**
 * \brief extracts server message from a packet
 * 
 * This extraction operator overload takes the data from the packet, and puts it into
 *  a message structure. If the command required any specific data to be sent along,
 *  then a new object will be created, and the pointers in the associated structure will
 *  point to the new object.
 * 
 * @param p a packet that was recieved from a client
 * @param h an empty client message 
 */
sf::Packet& operator>>(sf::Packet& p, Message::Server& h);

/**
 * \brief inserts a server message into a packet
 * 
 * @param p a packet which will be sent to the server
 * @param h the client message to send
 */
sf::Packet& operator<<(sf::Packet& p, const Message::Server& h);
#endif