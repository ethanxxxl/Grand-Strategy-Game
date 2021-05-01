#ifndef WORLD2_H
#define WORLD2_H

#include <vector>
#include <unordered_map>
#include <map>
#include <GameCore/Tile2.h>

// The world will be hexagonal tile grid. the grid have rotational symetry
// along all 6 sides.
class World
{
public:
    // x,y,z in hexagonal are axis in the three directions...
    // in this grid, coords will only be integers
    struct cube_coords_t
    {
        int x, y, z;
        friend cube_coords_t operator+(cube_coords_t& c1, cube_coords_t& c2);
        friend cube_coords_t operator-(cube_coords_t& c1, cube_coords_t& c2);
    }; 

    struct axial_coords_t { int q, r; };
    struct pixel_coords_t { double x, y; }; // because the grid is based off of hexes, there will be non integer cartesaian coords.o

    // hexagonal directions
    enum class DIRS { NE, N, NW, SW, S, SE };

    std::map<DIRS, cube_coords_t> CUBE_DIRS
    { 
        {DIRS::SE, {+1, -1, 0}}, {DIRS::NE, {+1, 0, -1}}, {DIRS::N, {0, +1, -1}}, 
        {DIRS::NW, {-1, +1, 0}}, {DIRS::SW, {-1, 0, +1}}, {DIRS::S, {0, -1, +1}}
    };


private:
    // maximum number of tiles in any direction from the central tile.
    int radius;
    // this is a 2D vector, where the coordinates are axial coordinates.
    // they they are stored by [q][r]
    std::map<cube_coords_t, Tile> world_data;

public:
    
    World(int radius);
    
    // map references
    Tile at(cube_coords_t coords);
    Tile at(axial_coords_t coords);

    axial_coords_t to_axial(cube_coords_t   coords); // convert from cube coordinates to axial coordinates
    axial_coords_t to_axial(pixel_coords_t  coords); // convert from pixel coordinates to axial coordinates, flat orientation //! not implemented
    cube_coords_t  to_cube (axial_coords_t  coords); // convert from axial coordnates to cube coordinates
    cube_coords_t  to_cube (pixel_coords_t  coords); // convert from pixel coordinates to cube coordinates, flat orientation //! not implemented
    pixel_coords_t to_pixel(cube_coords_t   coords); // convert from cube coordinates to pixel coordinates, flat orientation
    pixel_coords_t to_pixel(axial_coords_t  coords); // convert from axial coordinates to pixel coordinates, flat orientation 
};

#endif