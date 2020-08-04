#include <Company.h>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <CONSTANTS.h>
#include <Player.h>

Company::Company(int player_id, sf::Vector2i pos, int num_soldiers)
{
	this->player_id = player_id;
	this->position = pos;
	this->num_soldiers = num_soldiers;
}

Company::Company(int player_id, sf::Vector2i pos)
{
	this->player_id = player_id;
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
	position = new_pos;
}

sf::Vector2i Company::get_position()
{
	return position;
}

void Company::draw(sf::RenderTarget& target, sf::Color color)
{
	sf::CircleShape dot(display_radius);
	// use the player color
	dot.setFillColor(Player::player_by_id(player_id)->color);

	// vector2i isn't implicitly converted to vector2f
	using namespace CONSTANTS;
	sf::Vector2f pos = sf::Vector2f(tile_size*(position.x+0.5f)-display_radius, tile_size*(position.y+0.5f)-display_radius);
	dot.setPosition(pos);
	target.draw(dot);
}
