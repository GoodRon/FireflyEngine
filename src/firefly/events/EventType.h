/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_EVENT_TYPE_H
#define FIREFLY_EVENT_TYPE_H

namespace firefly {

enum class EventType: int {
	Unknown = 0,
	Native,
	System,
	Entity,
	GameState,
	Update,
	State,
	Kill,
	Collision,
	Position,
	SetSpeed,
	AddSpeed,
	SetAcceleration,
	AddAcceleration,
	SetFuel,
	Shoot,
	SetAmmunition
}; 

}

#endif // FIREFLY_EVENT_TYPE_H
