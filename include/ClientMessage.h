#ifndef CLIENTMESSAGE_H
#define CLIENTMESSAGE_H

#include <SFML/Network.hpp>
#include <string>

struct ConsolePrint
{
	// if you end up using this a lot, you could add more
	// options.
	std::string message;
};

struct SendChat
{};

struct GetMoves
{};

struct MoveUnit
{};

struct GetInfo
{};

/** operator overloads for each union member */
struct ClientMessage;
sf::Packet& operator<<(sf::Packet& p, const ClientMessage& h);

sf::Packet& operator<<(sf::Packet& p, const ConsolePrint& h);
sf::Packet& operator<<(sf::Packet& p, const SendChat& h);
sf::Packet& operator<<(sf::Packet& p, const GetMoves& h);
sf::Packet& operator<<(sf::Packet& p, const MoveUnit& h);
sf::Packet& operator<<(sf::Packet& p, const GetInfo& h);

/**
 * --ClientMessage--
 * this is a two component struct. It contains a header and a body
 * this is the header for messages from the client to the server.
 * It contains a specifier, describing the type of message, and 
 * data to identify which user is sending the message. 
 */
struct ClientMessage
{
	/** HEADER */
	enum class commands_t: uint16_t
	{
		CONSOLE_PRINT,
		SEND_CHAT,
		GET_MOVES,
		MOVE_UNIT,
		GET_INFO
	}
	command;

	//? do you want to add a "job number" so that the client knows exactly what
	//? command the message is referring to? if the need arises, this should be
	//? added.

	// may be used in the future;
	uint64_t player_ID;
	std::string username;

	/** BODY */
	union MessageBody
	{
		ConsolePrint 	console_print;
		SendChat     	send_chat;
		GetMoves     	get_moves;
		MoveUnit		move_unit;
		GetInfo 		get_info;
	} body;
};

#endif