#include <GameCore/CoordinateSystems/CubeCoords.h>

cube_coords_t operator+(const cube_coords_t& c1, const cube_coords_t& c2)
{
    return { c1.x+c2.x, c1.y+c2.y, c1.z+c2.z };
}

cube_coords_t operator-(const cube_coords_t& c1, const cube_coords_t& c2)
{
    return { c1.x+c2.x, c1.y+c2.y, c1.z+c2.z };
}

bool operator==(const cube_coords_t& c1, const cube_coords_t& c2)
{
    return ( c1.x == c2.x ) && ( c1.y == c2.y ) && ( c1.z == c2.z );
}

// TODO: implement an actual hashing function
std::size_t cubeHash::operator()(cube_coords_t const& c) const noexcept
{
    // do something
    return std::hash<int>{}(c.x + c.y);
}