#include <GameCore/World.h>
#include <GameCore/Tile.h>
#include <time.h>
#include <noise/noise.h>
#include <noise/module/perlin.h>

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
            pos = pos + CUBE_DIRS[DIRS::N];

        // SW
        for ( int i = 0; i <= rad; i++ )
        {
            world_data[pos] = {}; // insert an empty tile at pos
            pos = pos + CUBE_DIRS[DIRS::SW];
        }
        // S
        for ( int i = 0; i <= rad; i++ )
        {
            world_data[pos] = {}; // insert an empty tile at pos
            pos = pos + CUBE_DIRS[DIRS::S];
        }
        // SE
        for ( int i = 0; i <= rad; i++ )
        {
            world_data[pos] = {}; // insert an empty tile at pos
            pos = pos + CUBE_DIRS[DIRS::SE];
        }
        // NW
        for ( int i = 0; i <= rad; i++ )
        {
            world_data[pos] = {}; // insert an empty tile at pos
            pos = pos + CUBE_DIRS[DIRS::NW];
        }
        // N
        for ( int i = 0; i <= rad; i++ )
        {
            world_data[pos] = {}; // insert an empty tile at pos
            pos = pos + CUBE_DIRS[DIRS::N];
        }
        // NW
        for ( int i = 0; i <= rad; i++ )
        {
            world_data[pos] = {}; // insert an empty tile at pos
            pos = pos + CUBE_DIRS[DIRS::NW];
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


World::axial_coords_t World::to_axial(cube_coords_t   coords)
{
    return (axial_coords_t){coords.x, coords.y};
}

World::axial_coords_t World::to_axial(pixel_coords_t     coords)
{
    // TODO: implement this function
    return {};
}

World::cube_coords_t  World::to_cube (axial_coords_t  coords)
{
    return (cube_coords_t){coords.q, coords.r, -coords.q - coords.r };
}

World::cube_coords_t  World::to_cube (pixel_coords_t     coords)
{
    // TODO: implement this function
    return {};
}

World::pixel_coords_t World::to_pixel(cube_coords_t   coords)
{
    return (pixel_coords_t)
    {
        //.x = 3/2 * coords.x,
        .x = 0,
        .y = (sqrt(3)/2 * coords.x  +  sqrt(3) * coords.y)
    };
}

World::pixel_coords_t World::to_pixel(axial_coords_t  coords)
{
    return (pixel_coords_t)
    {
        //.x = (double)(3.0f/2.0f) * ((double)coords.q),
        .x = 0,
        .y = (sqrt(3)/2 * (double)coords.q  +  sqrt(3) * ((double)coords.r))
    };
}

World::cube_coords_t operator+(World::cube_coords_t& c1, World::cube_coords_t& c2)
{
    return { c1.x+c2.x, c1.y+c2.y, c1.z+c2.z };
}

World::cube_coords_t operator-(World::cube_coords_t& c1, World::cube_coords_t& c2)
{
    return { c1.x+c2.x, c1.y+c2.y, c1.z+c2.z };
}