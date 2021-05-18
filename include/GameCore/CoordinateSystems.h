#ifndef COORDINATESYSTEMS_H
#define COORDINATESYSTEMS_H

#include <GameCore/CoordinateSystems/AxialCoords.h>
#include <GameCore/CoordinateSystems/PixelCoords.h>
#include <GameCore/CoordinateSystems/CubeCoords.h>

#include <unordered_map>

namespace GameCore
{
    // hexagonal directions
    enum class directions_t { NE, N, NW, SW, S, SE, Begin=NE, End=SE };

    // "complement" operator, returns the side directly opposite d1
    directions_t operator~(const directions_t& d1);

    // Array of the directions, allows for easy looping over all directions
    extern const directions_t DIRECTIONS[(int)directions_t::End + 1];


    // Directional normals. Add these to a position, and the position will be
    //  shifted by one unit in that direction.
    const std::unordered_map<directions_t, cube_coords_t> DIRECTION_NORMALS
    { 
        {directions_t::SE, {+1, -1, 0}}, {directions_t::NE, {+1, 0, -1}}, {directions_t::N, {0, +1, -1}}, 
        {directions_t::NW, {-1, +1, 0}}, {directions_t::SW, {-1, 0, +1}}, {directions_t::S, {0, -1, +1}}
    };

    //? should I put these in a namespace?
    axial_coords_t to_axial(cube_coords_t   coords); // convert from cube coordinates to axial coordinates
    axial_coords_t to_axial(pixel_coords_t  coords); // convert from pixel coordinates to axial coordinates, flat orientation //! not implemented
    cube_coords_t  to_cube (axial_coords_t  coords); // convert from axial coordnates to cube coordinates
    cube_coords_t  to_cube (pixel_coords_t  coords); // convert from pixel coordinates to cube coordinates, flat orientation //! not implemented
    pixel_coords_t to_pixel(cube_coords_t   coords); // convert from cube coordinates to pixel coordinates, flat orientation
    pixel_coords_t to_pixel(axial_coords_t  coords); // convert from axial coordinates to pixel coordinates, flat orientation 
}

#endif