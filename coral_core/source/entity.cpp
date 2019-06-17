#include "entity.h"
#include <vector>
#include <assert.h>

using namespace coral;
using namespace core;

// 
static std::vector<Entity> m_entities;
// Only after if a entity is destroyed, it will be added to freelist. Otherwise just create from m_entities directly.
static std::vector<Entity> m_freeList;


Entity Entity::Create()
{
	// First reusing the destroyed entities.
	if (!m_freeList.empty())
	{
		// Index should be the same.
		Entity e = m_freeList.back();
		++e.m_version;
		m_freeList.pop_back();
		return e;
	}
	
	Entity e = Entity(m_entities.size() + 1, 0);
	m_entities.emplace_back(e);
	
	return e;
}

void Entity::Remove(Entity& id)
{
	++m_entities[id.m_id].m_version;
	// Copy  into the list
	m_freeList.push_back(id); 
}
