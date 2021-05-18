#ifndef GROUPING_H
#define GROUPING_H

#include <vector>
#include <GameCore/GameObject.h>

namespace GameCore
{
    class Grouping : public GameObject
    {
    public:
        enum class service_t { LAND, AIR, SEA };
        enum class specialty_t { ENGR, MED, SPEC_OP, NONE };

    private:
        service_t m_service;
        specialty_t m_specialty;
        int m_soldiers;
        int m_supplies;
        int m_ammunition;

        // recursive function which returns a list of coordinates which are at most r moves away from p
        void traverse_road(cube_coords_t p, directions_t travel, int r, std::vector<cube_coords_t>& road_tiles);

    public:
        // the distance that a group can move along roads.
        const int road_move_distance = 6;

        // returns a vector of all the valid moves which can be made from the current position
        const std::vector<cube_coords_t> get_valid_moves(void) override;

        // attempts to move the grouping to the new position.
        void move(const cube_coords_t& new_pos) override;
    };
}

#endif