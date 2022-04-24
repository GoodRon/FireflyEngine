/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_GAME_STATE_EVENT_H
#define FIREFLY_GAME_STATE_EVENT_H

#include "IEvent.h"

namespace firefly {

class GameStateEvent final: public IEvent {
public:
	GameStateEvent(int state);
	~GameStateEvent() override;

	int getState() const;

private:
	const int _state;
};

}

#endif // FIREFLY_GAME_STATE_EVENT_H
