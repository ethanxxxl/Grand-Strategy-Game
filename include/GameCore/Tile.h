#ifndef TILE2_H
#define TILE2_H

#include <GameCore/CoordinateSystems.h>
#include <set>

namespace GameCore
{
    enum class terrain_t { LAND, WATER, MOUNTAIN };

    // information related to a single point in the world.
    struct Tile
    {
        terrain_t terrain;
        float elevation;

        // these are the roads present on the tile.
        // they go clockwise around the tile, with 0 being a northern road
        std::set<directions_t> roads;
    };
}

#endif