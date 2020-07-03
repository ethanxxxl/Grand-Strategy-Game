#include <Company.h>

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

void Company::attack(Company &enemy_company)
{
	// this is a super simple combat algorithm, it will definitely change
	//  in the future.
	enemy_company.remove_soldiers(num_soldiers);
	this->remove_soldiers(enemy_company.get_soldiers());
}
