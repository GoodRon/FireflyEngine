/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_ADD_ACCELERATION_EVENT_H
#define FIREFLY_ADD_ACCELERATION_EVENT_H

#include "IEvent.h"
#include "Types.h"

namespace firefly {

class AddAccelerationEvent final: public IEvent {
public:
	AddAccelerationEvent(EntityID id,
		double acceleration, double direction);
	~AddAccelerationEvent() override;

	EntityID getId() const;
	double getAcceleration() const;
	double getDirection() const;

private:
	const EntityID _id;
	const double _acceleration;
	const double _direction;
};

}

#endif // FIREFLY_ADD_ACCELERATION_EVENT_H
