#ifndef TILE2_H
#define TILE2_H

#include <GameCore/CoordinateSystems.h>
#include <set>

namespace GameCore
{
    /// different types of terrain that a tile can have
    enum class terrain_t { LAND, WATER, MOUNTAIN };

    /**
     * \brief information related to a single point in the world 
     * 
     * The world will contain an `std::unordered_map` of these tiles.
     *  The tiles are hexagonal, and thus have 6 sides. additionally,
     *  each tile can have up to 6 roads, one for each side of the tile.
     */
    struct Tile
    {
        terrain_t terrain; ///< the terrain of the tile
        float elevation;   ///< the elevation of the tile

        /**
         * \brief the roads present on the tile
         * 
         * These are the roads present on the tile. They go clockwise
         *  around the tile, with 0 being a northern road
         */
        std::set<directions_t> roads;
    };
}

#endif