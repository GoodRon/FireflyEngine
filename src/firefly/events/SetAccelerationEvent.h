/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_SET_ACCELERATION_EVENT_H
#define FIREFLY_SET_ACCELERATION_EVENT_H

#include "IEvent.h"
#include "Types.h"

namespace firefly {

class SetAccelerationEvent final: public IEvent {
public:
	SetAccelerationEvent(EntityID id,
		double acceleration, double direction, 
		bool isConstant);
	~SetAccelerationEvent() override;

	EntityID getId() const;
	double getAcceleration() const;
	double getDirection() const;
	bool isConstant() const;

private:
	const EntityID _id;
	const double _acceleration;
	const double _direction;
	const bool _isConstant;
};

}

#endif // FIREFLY_SET_ACCELERATION_EVENT_H
