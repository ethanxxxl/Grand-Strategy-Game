#include <GameCore/GameObject.h>
#include <vector>
#include <algorithm>

std::vector<GameObject*> GameObject::m_objects = {};

GameObject::GameObject(unsigned int ID, World& world) : m_ID(ID), m_world(world)
{
    // make sure that each game object is in the list
    m_objects.push_back(this);
}

GameObject::~GameObject()
{
    // find 'this' in the objects list.
    auto result = std::find(m_objects.begin(), m_objects.end(), this);

    // erase any occurence of 'this' in objects list
    if ( result != m_objects.end() )
        m_objects.erase(result);
}

const std::vector<GameObject*>& GameObject::objects()
{
    return m_objects;
}