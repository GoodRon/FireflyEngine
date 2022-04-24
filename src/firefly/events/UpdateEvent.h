/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_UPDATE_EVENT_H
#define FIREFLY_UPDATE_EVENT_H

#include "IEvent.h"

namespace firefly {

class UpdateEvent final: public IEvent {
public:
	UpdateEvent();
	~UpdateEvent() override;
};

}

#endif // FIREFLY_UPDATE_EVENT_H
