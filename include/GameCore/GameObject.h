#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <GameCore/CoordinateSystems/CoordinateSystems.h>
#include <GameCore/World.h>
#include <string>
#include <vector>

class GameObject;
typedef std::vector<std::unique_ptr<GameObject>> gameobject_list_t;

class GameObject
{
private:
    static gameobject_list_t objects;
    cube_coords_t pos;
    const unsigned int ID;

    // references so that the object knows where it can move
    const World& world;
    //gameobject_list_t& objects;

public:
    std::string name;

    GameObject(unsigned int ID, World& world, gameobject_list_t& objects);
    virtual ~GameObject() = 0;

    cube_coords_t get_pos(void);
    virtual void change_position(cube_coords_t new_pos) = 0;
};

#endif