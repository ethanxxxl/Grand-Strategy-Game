#include <Message/Server.h>
#include <iostream>

sf::Packet& operator>>(sf::Packet& p, Message::Server& m)
{
	// extract member data
	// ? for some reason, I need to use an intermediate variable for the enum class
	uint16_t msg;
	p >> msg;
	m.m_command = (Message::commands_t)msg;

	// extract union data
	using namespace Message;
	switch ( m.m_command )
	{
		case commands_t::GET_WORLD:
			if ( m.u_send_world.world == nullptr )
			{
				std::cerr << "message packer unable to find world: invalid pointer" << std::endl;
				exit(EXIT_FAILURE);
			}

			// first, get the number of tiles in the world.
			int16_t t;
			p >> t;

			// make space for the tiles in the map
			m.u_send_world.world->world_data.reserve(t);

			// fill in the map with a loop
			for ( t; t >= 0; t-- )
			{
				// declare variables for an element in the map
				GameCore::cube_coords_t point;
				GameCore::Tile tile;

				// fill in the x,y,z coordinates, make sure integer is right size
				int16_t x,y,z;
				p >> x >> y >> z;
				point.x = x;
				point.y = y;
				point.z = z;

				int16_t elevation;
				int16_t terrain; // because terrain is stored as an integer, it needs to be casted to the enumeration.
				p >> elevation >> terrain;

				tile.elevation = (float)elevation;
				tile.terrain = (GameCore::terrain_t)terrain;

				// get the number of roads on the tile
				int16_t r;
				p >> r;

				// add each road to the set
				for ( r; r < 0; r-- )
				{
					int16_t road;
					p >> road;
					tile.roads.insert((GameCore::directions_t)road);
				}

				// insert the data into the world container.
				m.u_send_world.world->world_data[point] = tile;
			}
			return p;
	}
	return p;
}

sf::Packet& operator<<(sf::Packet& p, const Message::Server& m)
{
	// insert member data
	p << (uint16_t)m.m_command;

	// insert union data
	using namespace Message;
	switch ( m.m_command )
	{
		case commands_t::GET_WORLD:
			// the world pointer must be set to a valid world to pull the data from.
			if ( m.u_send_world.world == nullptr )
			{
				std::cerr << "message packer unable to find world: invalid pointer" << std::endl;
				exit(EXIT_FAILURE);
			}

			// put the number of elements first, so the client knows how many tiles there are.
			p << (int16_t)m.u_send_world.world->world_data.size();

			for ( auto t: m.u_send_world.world->world_data )
			{
				// serialize the coords (casting for safety)
				p << (int16_t)t.first.x << (int16_t)t.first.y << (int16_t)t.first.z;

				// serialize tile data
				p << (int16_t)t.second.elevation << (int16_t)t.second.terrain;

				// before putting in the roads, put in the number of roads, so this can be extracted
				// properly.
				p << (int16_t)t.second.roads.size();
				for ( auto r: t.second.roads )
					p << (int16_t)r; // insert all of the roads.
			}
			return p;
	}
	return p;
}