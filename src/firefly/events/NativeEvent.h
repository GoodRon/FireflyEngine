/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_NATIVE_EVENT_H
#define FIREFLY_NATIVE_EVENT_H

#include <SDL_events.h>

#include "IEvent.h"

namespace firefly {

class NativeEvent final: public IEvent {
public:
	NativeEvent(const SDL_Event& event);
	~NativeEvent() override;

	SDL_Event getSDLEvent() const;

private:
	const SDL_Event _event;
};

}

#endif // FIREFLY_NATIVE_EVENT_H
