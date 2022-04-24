/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include "IEvent.h"

namespace firefly {

IEvent::IEvent(EventType type):
	_type(type) {
}

IEvent::~IEvent() {
}

const EventType IEvent::getType() const {
	return _type;
}

}
