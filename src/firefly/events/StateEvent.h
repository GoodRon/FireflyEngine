/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_STATE_EVENT_H
#define FIREFLY_STATE_EVENT_H

#include "IEvent.h"
#include "Types.h"

namespace firefly {

class StateEvent final: public IEvent {
public:
	StateEvent(EntityID id, int state);
	~StateEvent() override;

	EntityID getId() const;
	int getState() const;

private:
	const EntityID _id;
	const int _state;
};

}

#endif // FIREFLY_STATE_EVENT_H
