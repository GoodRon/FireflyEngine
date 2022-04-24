/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_SET_SPEED_EVENT_H
#define FIREFLY_SET_SPEED_EVENT_H

#include "IEvent.h"
#include "Types.h"

namespace firefly {

class SetSpeedEvent final: public IEvent {
public:
	SetSpeedEvent(EntityID id, 
		double speed, double direction);
	~SetSpeedEvent() override;

	EntityID getId() const;
	double getSpeed() const;
	double getDirection() const;

private:
	const EntityID _id;
	const double _speed;
	const double _direction;
};

}

#endif // FIREFLY_SET_SPEED_EVENT_H
