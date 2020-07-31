#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <string>
#include <Company.h>
#include <vector>

class Player
{
private:
    // list of all player objects. When a new player object is constructed,
    //  it is automatically added to this list.
    static std::vector<Player*> players;

    // this is how assets will know what player they belong to.
    //  it is really just this players position in the players array.
    int player_id;

	std::vector<Company> companies;

public:

	Player(std::string username);
	~Player();

	std::string username;
	sf::Color color = sf::Color::Black;

	void draw(sf::RenderTarget& target);
	// returns pointer to a certain player when you only have the player id
	static Player* player_by_id(int id);
};

#endif
