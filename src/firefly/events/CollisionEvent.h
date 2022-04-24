/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_COLLISION_EVENT_H
#define FIREFLY_COLLISION_EVENT_H

#include "IEvent.h"
#include "Types.h"

namespace firefly {

class CollisionEvent final: public IEvent {
public:
	CollisionEvent(EntityID id);
	~CollisionEvent() override;

	EntityID getId() const;

private:
	const EntityID _id;
};

}

#endif // FIREFLY_COLLISION_EVENT_H
