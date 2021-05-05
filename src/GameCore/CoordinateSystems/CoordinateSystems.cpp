#include <GameCore/CoordinateSystems/CoordinateSystems.h>
#include <math.h>

axial_coords_t to_axial(cube_coords_t   coords)
{
    return (axial_coords_t){coords.x, coords.y};
}

axial_coords_t to_axial(pixel_coords_t     coords)
{
    // TODO: implement this function
    return {};
}

cube_coords_t  to_cube (axial_coords_t  coords)
{
    return (cube_coords_t){coords.q, coords.r, -coords.q - coords.r };
}

cube_coords_t  to_cube (pixel_coords_t     coords)
{
    // TODO: implement this function
    return {};
}

pixel_coords_t to_pixel(cube_coords_t   coords)
{
    return (pixel_coords_t)
    {
        .x = 3.0/2.0 * (double)(coords.x),
        .y = (sqrt(3)/2 * coords.x  +  sqrt(3) * coords.y)
    };
}

pixel_coords_t to_pixel(axial_coords_t  coords)
{
    return (pixel_coords_t)
    {
        .x = 3.0/2.0 * ((double)coords.q),
        .y = (sqrt(3)/2 * (double)coords.q  +  sqrt(3) * ((double)coords.r))
    };
}