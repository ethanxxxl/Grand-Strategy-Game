#include <GameCore/CoordinateSystems.h>
#include <math.h>

// actually define the directions, which was declared extern in the header file
const directions_t DIRECTIONS[] = { directions_t::NE,directions_t::N,directions_t::NW,directions_t::SW,directions_t::S,directions_t::SE };

// hahaha this is awesome and you know it
directions_t operator~(const directions_t& d1)
{
    switch ( d1 )
    {
        case directions_t::N:
            return directions_t::S; 
        case directions_t::NW:
            return directions_t::SE; 
        case directions_t::SW:
            return directions_t::NE; 
        case directions_t::SE:
            return directions_t::NW; 
        case directions_t::S:
            return directions_t::N; 
        case directions_t::NE:
            return directions_t::SW; 
        default:
            return directions_t::N; // this case should never occur
    }
}

axial_coords_t to_axial(cube_coords_t coords)
{
    return (axial_coords_t){coords.x, coords.y};
}

axial_coords_t to_axial(pixel_coords_t coords)
{
    // TODO: implement this function
    return {};
}

cube_coords_t to_cube (axial_coords_t coords)
{
    return (cube_coords_t){coords.q, coords.r, -coords.q - coords.r };
}

cube_coords_t  to_cube (pixel_coords_t coords)
{
    // TODO: implement this function
    return {};
}

pixel_coords_t to_pixel(cube_coords_t coords)
{
    return (pixel_coords_t)
    {
        .x = 3.0/2.0 * (double)(coords.x),
        .y = (sqrt(3)/2 * coords.x + sqrt(3) * coords.y)
    };
}

pixel_coords_t to_pixel(axial_coords_t coords)
{
    return (pixel_coords_t)
    {
        .x = 3.0/2.0 * ((double)coords.q),
        .y = (sqrt(3)/2 * (double)coords.q + sqrt(3) * ((double)coords.r))
    };
}