/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_ENTITY_REGISTRY_H
#define FIREFLY_ENTITY_REGISTRY_H

#include <memory>
#include <unordered_map>

namespace firefly {

class Entity;

class EntityPrototypes {
public:
	EntityPrototypes();
	~EntityPrototypes() = default;

	EntityPrototypes(const EntityPrototypes&) = delete;
	EntityPrototypes& operator=(const EntityPrototypes&) = delete;

	bool registerPrototype(const std::string& name, 
		const std::shared_ptr<Entity>& prototype);

	void removePrototype(const std::string& name);

	bool hasPrototype(const std::string& name) const;

	std::shared_ptr<Entity> makeEntity(const std::string& name) const;

	void clear();

private:
	std::unordered_map<std::string, std::unique_ptr<Entity>> _prototypes;
};

}

#endif // FIREFLY_ENTITY_REGISTRY_H
