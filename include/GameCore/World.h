#ifndef WORLD2_H
#define WORLD2_H

#include <vector>
#include <unordered_map>
#include <GameCore/Tile.h>
#include <GameCore/CoordinateSystems.h>

namespace GameCore
{
    /**
     * \brief class which manages the map
     * 
     * A world is a hexagonal tile grid. because the grid is hexagonal, it makes
     *  storing each tile challenging. The main coordinate system for this map are
     *  cubic coordinates. More about hexagonal coordinates systems can be found
     *  [here](https://www.redblobgames.com/grids/hexagons/#map-storage).
     * 
     * Because of the weird grid, the world is stored in a hash map, instead of a
     *  conventional 2D array.
     */
    class World
    {
    private:
        int radius; ///< maximum number of tiles in any direction from the central tile
        int seed;   ///< the seed used to generate the world

        public:
        // TODO: make this private
        /// contains the tile at every coordinate.
        std::unordered_map<cube_coords_t, Tile, cubeHash> world_data;

    public:
        /// default constructor, doesn't initialize anything
        World();

        /// \brief use this constructor, it initializes everything
        /// @param radius the maximum number of tiles in any direction from the central tile
        /// @param seed the seed used to generate the world
        World(int radius, int seed);

        /// When `world_data` is private (which it will be), this is the means to access individual tiles.
        /// @param coords the coordinates of the tile to reference
        Tile& at(cube_coords_t coords);  
        /// When `world_data` is private (which it will be), this is the means to access individual tiles.
        /// @param coords the coordinates of the tile to reference
        Tile& at(axial_coords_t coords);
    };
}

#endif