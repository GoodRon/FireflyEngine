/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_POSITION_EVENT_H
#define FIREFLY_POSITION_EVENT_H

#include "IEvent.h"
#include "Types.h"

namespace firefly {

class PositionEvent final: public IEvent {
public:
	PositionEvent(EntityID id, 
		double x, double y, double direction);
	~PositionEvent() override;

	EntityID getId() const;
	double getX() const;
	double getY() const;
	double getDirection() const;

private:
	const EntityID _id;
	const double _x;
	const double _y;
	const double _direction;
};

}

#endif // FIREFLY_POSITION_EVENT_H
