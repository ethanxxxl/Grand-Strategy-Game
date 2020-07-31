#ifndef COMPANY_H
#define COMPANY_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class Company
{
private:
	int num_soldiers = 150;
	static const int display_radius = 3;
	sf::Vector2i position;

	// this is the ID of the player that owns this company.
	int player_id;

public:
	Company(int player_id, sf::Vector2i pos, int num_soldiers);
	Company(int player_id, sf::Vector2i pos);

	int get_soldiers();
	void remove_soldiers(int num);
	void add_soldiers(int num);

	static void fight(Company attacker, Company defender);

	void move(sf::Vector2i new_pos);
	sf::Vector2i get_position();

	// draws the company at pos
	void draw(sf::RenderTarget& target, sf::Color color);
};


#endif
