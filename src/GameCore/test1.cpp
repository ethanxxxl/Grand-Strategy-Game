#include <GameCore/World.h>
#include <iostream>

int main()
{
    // create a world with radius of 5
    World w1(5);
    
    std::cout << w1.at({1,-1,0}).elevation << std::endl;

    return 0;
}