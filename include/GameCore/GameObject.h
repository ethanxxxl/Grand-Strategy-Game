#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <GameCore/CoordinateSystems.h>
#include <GameCore/World.h>
#include <memory>
#include <string>
#include <vector>

namespace GameCore
{
    class GameObject
    {
    private:
        // all objects that exist
        static std::vector<GameObject*> m_objects;

    protected:
        // position of the GameObject
        cube_coords_t m_pos;

        // the world that the object exists in.
        World& m_world;

    public:
        std::string m_name;
        const unsigned int m_ID;

        GameObject(unsigned int ID, World& world);
        virtual ~GameObject();

        const cube_coords_t& pos(void);
        static const std::vector<GameObject*>& objects(void);
        static GameObject* lookup(unsigned int ID);

        virtual const std::vector<cube_coords_t> get_valid_moves(void) = 0;
        virtual void move(const cube_coords_t& new_pos) = 0;
    };
}

#endif