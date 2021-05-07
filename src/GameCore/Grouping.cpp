#include <GameCore/Grouping.h>
#include <GameCore/CoordinateSystems.h>
#include <GameCore/World.h>
#include <GameCore/Tile.h>
#include <algorithm>
#include <ranges>

//! bug alert! the input vector must be an empty vector. this needs fixed!
void Grouping::traverse_road(cube_coords_t p, directions_t travel, int r, std::vector<cube_coords_t>& road_tiles)
{
    if ( road_tiles.size() == 0 )
    {
        // this is the first iteration, no to check and see if r is too small.
        // if there are no roads on p, then exit without doing anything
        // else, add the current tile to the list, and loop through all the roads
        if ( m_world.at(p).roads.size() == 0 )
            return;
        
        // add p to the list of valid moves (even though it is the same tile the object is on)
        //  and for each direction, call this function on the adjacent tile.
        road_tiles.push_back(p);
        for ( auto& road: m_world.at(p).roads )
            traverse_road(p + DIRECTION_NORMALS.at(road), road, r-1, road_tiles);
    }
    // check the distance, if it is 0, we are done with this chain.
    else if ( r <= 0 )
        return;
    else
    {
        // this is a potentially valid tile. If it doesn't have any roads, its invalid.
        if ( m_world.at(p).roads.size() == 0 )
            return;

        // if none of the roads that p has complement 'travel' then this tile is invalid
        if ( std::ranges::none_of(m_world.at(p).roads, [travel](directions_t dir){return dir == ~travel;}) )
            return;

        // add the tile to "road tiles"
        // loop through the directions, except the complement of travel, and call this function
        //  on each of them
        road_tiles.push_back(p);
        for ( auto& road: m_world.at(p).roads )
        {
            traverse_road(p + DIRECTION_NORMALS.at(road), road, r-1, road_tiles);
        }
    }
}

const std::vector<cube_coords_t> Grouping::get_valid_moves(void)
{
    // the vector to return
    std::vector<cube_coords_t> valid_moves {};

    /** Get moves along roads
     *   this will populate the vector with all of the road tiles
     */
    traverse_road(m_pos, directions_t::N, 6, valid_moves);
    /** Add adjacent moves first
     */

    // then, add all of the adjacent tiles which aren't water
    for ( auto& d: DIRECTIONS )
    {
        cube_coords_t adjacent_pos = m_pos + DIRECTION_NORMALS.at(d);
        if ( m_world.at(adjacent_pos).terrain != terrain_t::WATER )
            valid_moves.push_back(adjacent_pos);
    }

    // TODO figure out how to sort your data, then remove the duplicates. consider using a set.
    return {};
    //return std::ranges::unique(valid_moves, [](cube_coords_t d1, cube_coords_t d2){return d1==d2;});
}

void Grouping::move(const cube_coords_t& new_pos)
{

}