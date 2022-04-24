/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_IEVENT_H
#define FIREFLY_IEVENT_H

#include "EventType.h"

namespace firefly {

class IEvent {
public:
	IEvent(EventType type);
	virtual ~IEvent() = 0;

	const EventType getType() const;

private:
	const EventType _type;
};

}

#endif // FIREFLY_IEVENT_H
