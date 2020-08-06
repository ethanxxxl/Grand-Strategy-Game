#include <iostream>
#include <Company.h>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <CONSTANTS.h>
#include <memory>

#include <Player.h>
#include <World.h>

Company::Company(Player* player, World* world, sf::Vector2i pos, int num_soldiers)
{
	Company(player, world, pos);
	this->num_soldiers = num_soldiers;
}

Company::Company(Player* player, World* world, sf::Vector2i pos)
{
	this->player = player;
	this->world = world;
	this->position = pos;
	
	// update the position in the world
	world->at(pos)->company = this;
	
	// add this company to the player list
	player->companies.push_back(this);
}


int Company::get_soldiers()
{
	return num_soldiers;
}

void Company::remove_soldiers(int num)
{
	num_soldiers -= num;
	if ( num_soldiers < 0 )
		num_soldiers = 0;
}

void Company::add_soldiers(int num)
{
	num_soldiers += num;
}

void Company::fight(Company attacker, Company defender)
{
	// this is a super simple combat algorithm, it will definitely change
	//  in the future.
	defender.remove_soldiers(attacker.get_soldiers());
	attacker.remove_soldiers(defender.get_soldiers());
}

void Company::move(sf::Vector2i new_pos)
{
	// TODO add limits on how far a company can move per turn
	
	// bounds cheching
	if ( ( new_pos.x >= 0 and new_pos.x < world->get_size().x ) and \
		 ( new_pos.y >= 0 and new_pos.y < world->get_size().y ) )
	{
		// remove the company from the old tile
		world->at(position)->company = NULL;
		// put the company on the new tile
		world->at(new_pos)->company = this;

		// update the new position
		position = new_pos;
	}
}

void Company::move(Tile* new_tile)
{
	move(new_tile->get_pos());
}

sf::Vector2i Company::get_position()
{
	return position;
}

void Company::draw(sf::RenderTarget& target, sf::Color color)
{
	sf::CircleShape dot(display_radius);
	// use the player color
	dot.setFillColor(player->color);

	// vector2i isn't implicitly converted to vector2f
	using namespace CONSTANTS;
	sf::Vector2f pos = sf::Vector2f(tile_size*(position.x+0.5f)-display_radius, tile_size*(position.y+0.5f)-display_radius);
	dot.setPosition(pos);
	target.draw(dot);
}
