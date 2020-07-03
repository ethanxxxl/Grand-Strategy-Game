#ifndef COMPANY_H
#define COMPANY_H

class Company
{
private:
	int num_soldiers;

	// TODO: think about using smart pointers for the location of items.
	// TODO: figure out how you are going to structure this stuff.

public:
	int get_soldiers();
	void remove_soldiers(int num);
	void add_soldiers(int num);

	void attack(Company &enemy_company);

	void move(int x, int y);
};


#endif
