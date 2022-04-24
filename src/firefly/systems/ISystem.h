/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_ISYSTEM_H
#define FIREFLY_ISYSTEM_H

#include <atomic>
#include <string>
#include <memory>
#include <unordered_map>
#include <unordered_set>

#include "Types.h"

namespace firefly {

class IEvent;
class Entity;
class Engine;

class ISystem {
public:
	ISystem(const std::string& name,
		Engine* engine);

	virtual ~ISystem() = 0;

	ISystem(const ISystem&) = delete;
	ISystem& operator=(const ISystem&) = delete;

	const std::string getName() const;

	bool processEvent(const std::shared_ptr<IEvent>& event);

	void setActive(bool isActive);
	bool isActive() const;

protected:
	void addRequiredComponent(const std::string& name);
	bool checkComponents(Entity* entity) const;

	Engine* getEngine() const;
	const std::unordered_map<EntityID, Entity*>& getEntities() const;

	uint64_t getElapsedMs() const;
	uint64_t getLastUpdateTimepoint() const;

	virtual bool onEvent(
		const std::shared_ptr<IEvent>& event);
	virtual void onUpdate();
	virtual bool onRegisterEntity(Entity* entity);
	virtual void onUnregisterEntity(Entity* entity);

	Entity* getEntity(EntityID id) const;

private:
	bool registerEntity(Entity* entity);
	void unregisterEntity(EntityID id);

private:
	const std::string _name;
	Engine* const _engine;
	bool _isActive;
	std::unordered_set<std::string> _requiredComponents;
	std::unordered_map<EntityID, Entity*> _entities;
	std::atomic<uint64_t> _updateTimepoint;
};

}

#endif // FIREFLY_ISYSTEM_H
