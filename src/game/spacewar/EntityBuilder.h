/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_ENTITY_BUILDER_H
#define SW_ENTITY_BUILDER_H

#include <memory>
#include <string>

namespace firefly {
	class Engine;
	class Entity;
}

namespace spacewar {

class EntityBuilder {
public:
	EntityBuilder(firefly::Engine* engine);
	~EntityBuilder();

	EntityBuilder(EntityBuilder&&) = default;
	EntityBuilder& operator=(EntityBuilder&&) = default;

	std::shared_ptr<firefly::Entity> buildEntity(
		const std::string& jsonConfig);

private:
	class Impl;
	std::unique_ptr<Impl> _impl;
};

}

#endif // SW_ENTITY_BUILDER_H
