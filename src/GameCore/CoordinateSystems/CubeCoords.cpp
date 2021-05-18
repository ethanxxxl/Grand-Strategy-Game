#include <GameCore/CoordinateSystems/CubeCoords.h>

namespace GameCore
{
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

    std::size_t cubeHash::operator()(cube_coords_t const& c) const noexcept
    {
        // do something
        const unsigned int HASH_CONST = 0x6AB4FC53; // just a random number
        const unsigned int hash = ( HASH_CONST << c.x ) ^ ( HASH_CONST << c.y );
        return (std::size_t)hash;
    }
}