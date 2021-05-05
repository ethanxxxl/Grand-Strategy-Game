#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <GameCore/CoordinateSystems/CoordinateSystems.h>
#include <GameCore/World.h>
#include <memory>
#include <string>
#include <vector>

class GameObject
{
private:
    cube_coords_t m_pos;

    // references so that the object knows where it can move
    const World& m_world;

    // all objects that exist
    static std::vector<GameObject*> m_objects;

public:
    std::string m_name;
    const unsigned int m_ID;

    GameObject(unsigned int ID, World& world);
    virtual ~GameObject();

    cube_coords_t get_pos(void);
    virtual void change_position(cube_coords_t new_pos) = 0;

    static const std::vector<GameObject*>& objects();
};

#endif