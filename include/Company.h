#ifndef COMPANY_H
#define COMPANY_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <Entity.h>
#include <Player.h>

class Company;
#include <GraphicsManager.h>

class Company : public Entity
{
private:
	int num_soldiers = 150;
	sf::Vector2i position;

	

public:
	// this is the player that owns this company
	Player& player;

	Company(Player& player, sf::Vector2i pos, int num_soldiers);
	Company(Player& player, sf::Vector2i pos);

	int get_soldiers();
	void remove_soldiers(int num);
	void add_soldiers(int num);

	static void fight(Company& attacker, Company& defender);

	void move(sf::Vector2i new_pos);
	void move(Tile* new_tile);
	sf::Vector2i get_position();

	// draws the company at pos
	void draw(GraphicsManager &gm);
};


#endif
