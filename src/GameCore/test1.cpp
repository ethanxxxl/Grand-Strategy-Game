#include <GameCore/World.h>
#include <iostream>
#include <iomanip>

int main()
{
    // create a world with radius of 5
    World w1(5);

    //std::cout << std::right;
    // if world data is not private, this works.
    ///for ( auto& [first,second]: w1.world_data )
    //    std::cout << std::setw(10) << second.elevation << " @ " << "<" << std::setw(2)<< first.x << ", " << std::setw(2)<<first.y << ", " <<  std::setw(2)<<first.z << ">\n";

    return 0;
}