#ifndef GROUPING_H
#define GROUPING_H

#include <vector>
#include <GameCore/GameObject.h>

namespace GameCore
{
    /**
     * \brief a grouping of soldiers, seamen, or airmen
     * 
     * A grouping is a `GameCore::GameObject` which represents a unit of militery servicemen.
     *  These units can be any size, and there will be limitations corresponding to the level
     *  of organization on the size of the grouping.
     * 
     * These groups are service agnostic, and each grouping can have a specialty
     */
    class Grouping : public GameObject
    {
    public:
        enum class service_t { LAND, AIR, SEA };             ///< available services the grouping may be a part of
        enum class specialty_t { ENGR, MED, SPEC_OP, NONE }; ///< specialties that the group may have

    private:
        service_t m_service;     ///< The service that the group belongs to
        specialty_t m_specialty; ///< the specialty of this group
        int m_soldiers;          ///< number of soldiers in this group
        int m_supplies;          ///< amount of supplies the group has left (these are absolute unit, ie. rations)
        int m_ammunition;        ///< ammount of ammunition the group has left (these are absolute units)

        /// recursive function which returns a list of coordinates which are at most r moves away from p
        void traverse_road(cube_coords_t p, directions_t travel, int r, std::vector<cube_coords_t>& road_tiles);

    public:
        /// the distance that a group can move along roads.
        const int road_move_distance = 6;

        /// returns a vector of all the valid moves which can be made from the current position
        const std::vector<cube_coords_t> get_valid_moves(void) override;

        /// attempts to move the grouping to the new position.
        void move(const cube_coords_t& new_pos) override;
    };
}

#endif