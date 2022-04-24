/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_KILL_EVENT_H
#define FIREFLY_KILL_EVENT_H

#include "IEvent.h"
#include "Types.h"

namespace firefly {

class KillEvent final: public IEvent {
public:
	KillEvent(EntityID id);
	~KillEvent() override;

	EntityID getId() const;

private:
	const EntityID _id;
};

}

#endif // FIREFLY_KILL_EVENT_H
