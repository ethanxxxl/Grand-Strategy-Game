#include <GameCore/GameObject.h>

GameObject::GameObject(unsigned int ID, World& world, gameobject_list_t& objects) :
this->ID(ID),
this->world(world),
this->objects(objects)
{
    objects.push_back(this);
}