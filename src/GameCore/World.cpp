#include <GameCore/World.h>
#include <GameCore/Tile.h>
#include <FastNoiseLite.h>
#include <GameCore/CoordinateSystems.h>


namespace GameCore
{
    World::World()
    { }

    World::World(int radius, int seed)
    {
        this->radius = radius;
        this->seed = seed;

        // create enough space for the size of the board
        // go through the board, get the cartesian coordinate, then apply noise
        //  to get the data for the tile.
        int num_tiles = 0;

        // expression for total number of tiles on the board
        for ( int r = 1; r <= radius; r++ )
            num_tiles += r;
        num_tiles *= 6;

        world_data = {};
        // make enough space for all the tiles
        //world_data.reserve(num_tiles);

        // insert blank tiles into the map
        for ( int rad = 0; rad <= radius; rad++ )
        {
            cube_coords_t pos = {0,0,0};

            // move the starting position to the topmost position
            for ( int i = 0; i <= rad; i++ )
                pos = pos + DIRECTION_NORMALS.at(directions_t::N);

            // SW
            for ( int i = 0; i <= rad; i++ )
            {
                world_data[pos] = {}; // insert an empty tile at pos
                pos = pos + DIRECTION_NORMALS.at(directions_t::SW);
            }
            // S
            for ( int i = 0; i <= rad; i++ )
            {
                world_data[pos] = {}; // insert an empty tile at pos
                pos = pos + DIRECTION_NORMALS.at(directions_t::S);
            }
            // SE
            for ( int i = 0; i <= rad; i++ )
            {
                world_data[pos] = {}; // insert an empty tile at pos
                pos = pos + DIRECTION_NORMALS.at(directions_t::SE);
            }
            // NE
            for ( int i = 0; i <= rad; i++ )
            {
                world_data[pos] = {}; // insert an empty tile at pos
                pos = pos + DIRECTION_NORMALS.at(directions_t::NW);
            }
            // N
            for ( int i = 0; i <= rad; i++ )
            {
                world_data[pos] = {}; // insert an empty tile at pos
                pos = pos + DIRECTION_NORMALS.at(directions_t::N);
            }
            // NW
            for ( int i = 0; i <= rad; i++ )
            {
                world_data[pos] = {}; // insert an empty tile at pos
                pos = pos + DIRECTION_NORMALS.at(directions_t::NW);
            }

            world_data[pos] = {}; // since I was incrementing before, I need to
                                        // add the last value I was working on

        }

        // go through each tile and generate noise for them.
        // initialize the noise engine
        FastNoiseLite noise;
        noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
        noise.SetSeed(seed);

        // give some perlin noise to all of the tiles.
        // TODO: Tune this section
        int i = 0;
        for ( auto& [first, second]: world_data )
        {
            auto coord = to_pixel(first);
            second.elevation = 10*noise.GetNoise((float)coord.x, (float)coord.y);

            if ( second.elevation < 0 )
                second.terrain = terrain_t::WATER;
            else if ( second.elevation < 7 )
                second.terrain = terrain_t::LAND;
            else
                second.terrain = terrain_t::MOUNTAIN;
        }
    }

    Tile& World::at(cube_coords_t coords)
    {
        return world_data[coords];
    }

    Tile& World::at(axial_coords_t coords)
    {
        return world_data[to_cube(coords)];
    }
}