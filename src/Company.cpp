#include <iostream>
#include <Company.h>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <CONSTANTS.h>
#include <memory>

Company::Company(Player& player, sf::Vector2i pos, int num_soldiers) : player(player)
{
	this->position = pos;
	this->num_soldiers = num_soldiers;
}

Company::Company(Player& player, sf::Vector2i pos) : player(player)
{
	this->position = pos;
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

void Company::fight(Company& attacker, Company& defender)
{
	// this is a super simple combat algorithm, it will definitely change
	//  in the future.
	defender.remove_soldiers(attacker.get_soldiers());
	attacker.remove_soldiers(defender.get_soldiers());
}

void Company::move(sf::Vector2i new_pos)
{
	// TODO add limits on how far a company can move per turn
	// TODO fix this to work with the new system
	
	// bounds cheching
	//if ( ( new_pos.x >= 0 and new_pos.x < world->get_size().x ) and \
		 ( new_pos.y >= 0 and new_pos.y < world->get_size().y ) )
	{
		// remove the company from the old tile
		//world->at(position)->company = NULL;
		// put the company on the new tile
		//world->at(new_pos)->company = this;

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

void Company::draw(GraphicsManager &gm)
{
	gm.draw_company(*this);
}
