#ifndef COORDINATESYSTEMS_H
#define COORDINATESYSTEMS_H

#include <GameCore/CoordinateSystems/AxialCoords.h>
#include <GameCore/CoordinateSystems/PixelCoords.h>
#include <GameCore/CoordinateSystems/CubeCoords.h>

#include <unordered_map>

// hexagonal directions
enum class DIRS { NE, N, NW, SW, S, SE };

// Directional normals. Add these to a position, and the position will be
//  shifted by one unit in that direction.
const std::unordered_map<DIRS, cube_coords_t> CUBE_DIRS
{ 
    {DIRS::SE, {+1, -1, 0}}, {DIRS::NE, {+1, 0, -1}}, {DIRS::N, {0, +1, -1}}, 
    {DIRS::NW, {-1, +1, 0}}, {DIRS::SW, {-1, 0, +1}}, {DIRS::S, {0, -1, +1}}
};

//? should I put these in a namespace?
axial_coords_t to_axial(cube_coords_t   coords); // convert from cube coordinates to axial coordinates
axial_coords_t to_axial(pixel_coords_t  coords); // convert from pixel coordinates to axial coordinates, flat orientation //! not implemented
cube_coords_t  to_cube (axial_coords_t  coords); // convert from axial coordnates to cube coordinates
cube_coords_t  to_cube (pixel_coords_t  coords); // convert from pixel coordinates to cube coordinates, flat orientation //! not implemented
pixel_coords_t to_pixel(cube_coords_t   coords); // convert from cube coordinates to pixel coordinates, flat orientation
pixel_coords_t to_pixel(axial_coords_t  coords); // convert from axial coordinates to pixel coordinates, flat orientation 

#endif