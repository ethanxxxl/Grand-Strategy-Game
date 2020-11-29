#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/System/Vector2.hpp>
#include <Player.h>
#include <string>

class Entity
{
private:
	sf::Vector2i position;
	Player* player;
	std::string name;

public:
	Entity();
	virtual void draw() = 0;
	virtual void move() = 0;
};


#endif
