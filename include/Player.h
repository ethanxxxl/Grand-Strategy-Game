#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <Company.h>
#include <vector>

class Player
{
private:
	int troops;
	std::vector<Company> companies;

public:
	std::string username;

};

#endif
