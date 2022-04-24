/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_ENTITY_EVENT_H
#define FIREFLY_ENTITY_EVENT_H

#include <memory>

#include "IEvent.h"

namespace firefly {

class Entity;

class EntityEvent final: public IEvent {
public:
	EntityEvent(const std::shared_ptr<Entity>& entity,
		bool isRemoved = false);
	~EntityEvent() override;

	std::shared_ptr<Entity> getEntity() const;

	bool isRemoved() const;

private:
	const std::shared_ptr<Entity> _entity;
	const bool _isRemoved;
};

}

#endif // FIREFLY_ENTITY_EVENT_H
