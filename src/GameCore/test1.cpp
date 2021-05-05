#include <GameCore/World.h>
#include <iostream>
#include <iomanip>
#include <time.h>

int main()
{
    srand(time(NULL));
    
    // create a world with radius of 5
    World w1(5, rand());

    std::cout << std::right;
    //if world data is not private, this works.
    for ( auto& [first,second]: w1.world_data) 
    {
        std::cout << std::setw(10) << second.elevation << " @ " << "<" << std::setw(2)<< first.x << ", " << std::setw(2)<<first.y << ", " <<  std::setw(2)<<first.z << ">";
        switch (second.terrain)
        {
            case terrain_t::LAND:
                std::cout << " LAND ";
                break;
            case terrain_t::WATER:
                std::cout << " WATER ";
                break;
            case terrain_t::MOUNTAIN:
                std::cout << " MOUNTAIN ";
                break;
        }

        std::cout << std::endl;
    }   

    return 0;
}