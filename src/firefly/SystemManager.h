/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_SYSTEM_MANAGER_H
#define FIREFLY_SYSTEM_MANAGER_H

#include <string>
#include <unordered_map>
#include <memory>

#include "Types.h"

namespace firefly {

class ISystem;
class IEvent;
class Entity;
class EventManager;

class SystemManager {
public:
	SystemManager(
		EventManager* eventManager);
	~SystemManager();

	SystemManager(const SystemManager&) = delete;
	SystemManager& operator=(const SystemManager&) = delete;

	bool addSystem(const std::shared_ptr<ISystem>& system);
	void removeSystem(const std::string& name);
	
	bool hasSystem(const std::string& name) const;
	std::shared_ptr<ISystem> getSystem(const std::string& name);

	bool processEvent(
		const std::shared_ptr<IEvent>& event);

	void clear();

private:
	EventManager* const _eventManager;
	std::unordered_map<std::string, std::shared_ptr<ISystem>> _systems;
};

}

#endif // FIREFLY_SYSTEM_MANAGER_H
