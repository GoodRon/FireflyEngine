/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_OBJECT_MANAGER_H
#define FIREFLY_OBJECT_MANAGER_H

#include <vector>
#include <unordered_map>
#include <forward_list>
#include <memory>

#include "Types.h"

namespace firefly {

class Entity;
class EventManager;

class EntityManager {
public:
	EntityManager(
		EventManager* eventManager);
	~EntityManager();

	EntityManager(const EntityManager&) = delete;
	EntityManager& operator=(EntityManager&) = delete;

	bool addEntity(const std::shared_ptr<Entity>& entity);
	void removeEntity(EntityID id);

	bool hasEntity(EntityID id) const;
	std::shared_ptr<Entity> getEntity(EntityID id);

	std::forward_list<EntityID> getIds() const;

	void clear();

private:
	EventManager* const _eventManager;
	std::unordered_map<EntityID, std::shared_ptr<Entity>> _entities;
};

}

#endif // FIREFLY_OBJECT_MANAGER_H
