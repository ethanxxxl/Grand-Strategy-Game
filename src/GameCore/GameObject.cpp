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

GameObject* GameObject::lookup(unsigned int ID)
{
	// lambda for easy checking of ID
	auto check_ID = [ID](GameObject* o) { return o->m_ID == ID; };

	// the objects we are looking through
	const std::vector<GameObject*> objs = GameObject::objects();

	// find the object, if it is not in the list, then return an empty set of valid moves.
	auto result = std::ranges::find_if(objs, check_ID);
	if ( result == objs.end() )
		return {};

    return *result;
}

const std::vector<GameObject*>& GameObject::objects(void)
{
    return m_objects;
}

const cube_coords_t& GameObject::pos(void)
{
    return m_pos;
}