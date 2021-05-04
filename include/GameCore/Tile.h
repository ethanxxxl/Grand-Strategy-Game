#ifndef TILE2_H
#define TILE2_H

enum class terrain_t { LAND, WATER, MOUNTAIN };

// information related to a single point in the world.
struct Tile
{
    terrain_t terrain;
    float elevation;
};

#endif