#ifndef WORLD2_H
#define WORLD2_H

#include <vector>
#include <unordered_map>
#include <GameCore/Tile.h>
#include <GameCore/CoordinateSystems.h>

// The world is be hexagonal tile grid. the grid have rotational symetry
// along all 6 sides.
class World
{
private:
    // maximum number of tiles in any direction from the central tile.
    int radius;
    int seed;

    //? add a way to access elements using axial coords?
    // world data storage.
    public:
    std::unordered_map<cube_coords_t, Tile, cubeHash> world_data;

public:
    World();
    World(int radius, int seed);
    
    // map references
    Tile& at(cube_coords_t coords);
    Tile& at(axial_coords_t coords);

};

#endif