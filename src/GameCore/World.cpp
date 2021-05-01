#include <GameCore/World.h>
#include <GameCore/Tile.h>
#include <time.h>
#include <noise/noise.h>
#include <noise/module/perlin.h>
#include <GameCore/CoordinateSystems/CoordinateSystems.h>

World::World(int radius)
{
    this->radius = radius;

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
            pos = pos + CUBE_DIRS.find(DIRS::N)->second;

        // SW
        for ( int i = 0; i <= rad; i++ )
        {
            world_data[pos] = {}; // insert an empty tile at pos
            pos = pos + CUBE_DIRS.find(DIRS::SW)->second;
        }
        // S
        for ( int i = 0; i <= rad; i++ )
        {
            world_data[pos] = {}; // insert an empty tile at pos
            pos = pos + CUBE_DIRS.find(DIRS::S)->second;
        }
        // SE
        for ( int i = 0; i <= rad; i++ )
        {
            world_data[pos] = {}; // insert an empty tile at pos
            pos = pos + CUBE_DIRS.find(DIRS::SE)->second;
        }
        // NE
        for ( int i = 0; i <= rad; i++ )
        {
            world_data[pos] = {}; // insert an empty tile at pos
            pos = pos + CUBE_DIRS.find(DIRS::NW)->second;
        }
        // N
        for ( int i = 0; i <= rad; i++ )
        {
            world_data[pos] = {}; // insert an empty tile at pos
            pos = pos + CUBE_DIRS.find(DIRS::N)->second;
        }
        // NW
        for ( int i = 0; i <= rad; i++ )
        {
            world_data[pos] = {}; // insert an empty tile at pos
            pos = pos + CUBE_DIRS.find(DIRS::NW)->second;
        }

        world_data[pos] = {}; // since I was incrementing before, I need to
                                    // add the last value I was working on

    }

    // go through each tile and generate noise for them.
    // initialize the noise engine
	noise::module::Perlin noise_module;
	srand(time(NULL));
	noise_module.SetSeed(rand());

    // give some perlin noise to all of the tiles.
    // TODO: Tune this section
    for ( auto i = world_data.begin(); i != world_data.end(); i++ )
    {
        auto coord = to_pixel(i->first);
        i->second.elevation = noise_module.GetValue(coord.x, coord.y, 1);

        // set the terrain based on the elevation
        // ? you might want to do this differently
        // TODO: implement this
    }
}

Tile World::at(cube_coords_t coords)
{
    return world_data[coords];
}

Tile World::at(axial_coords_t coords)
{
    return world_data[to_cube(coords)];
}