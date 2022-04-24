/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include "EntityManager.h"

#include "Entity.h"
#include "EventManager.h"

#include "events/EntityEvent.h"

namespace firefly {

EntityManager::EntityManager(
	EventManager* eventManager):
	_eventManager(eventManager) {
}

EntityManager::~EntityManager() {
}

bool EntityManager::addEntity(
	const std::shared_ptr<Entity>& entity) {

	if (!entity) {
		return false;
	}

	const auto id = entity->getId();
	if (hasEntity(id)) {
		return true;
	}

	_entities[id] = entity;

	std::shared_ptr<IEvent> event(new EntityEvent(
		entity));
	_eventManager->registerEvent(std::move(event));
	return true;
}

void EntityManager::removeEntity(EntityID id) {
	if (!hasEntity(id)) {
		return;
	}

	std::shared_ptr<IEvent> event(new EntityEvent(
		_entities[id], true));
	_eventManager->registerEvent(std::move(event));

	_entities.erase(id);
}

bool EntityManager::hasEntity(EntityID id) const {
	if (_entities.find(id) != _entities.end()) {
		return true;
	}
	return false;
}

std::shared_ptr<Entity> 
EntityManager::getEntity(EntityID id) {
	if (!hasEntity(id)) {
		return nullptr;
	}
	return _entities[id];
}

std::forward_list<EntityID> 
EntityManager::getIds() const {
	std::forward_list<EntityID> ids;
	for (auto& entity: _entities) {
		ids.push_front(entity.first);
	}
	return ids;
}

void EntityManager::clear() {
	_entities.clear();
}

}
