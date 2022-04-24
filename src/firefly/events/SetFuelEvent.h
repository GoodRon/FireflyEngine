/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_SET_FUEL_EVENT_H
#define FIREFLY_SET_FUEL_EVENT_H

#include "IEvent.h"
#include "Types.h"

namespace firefly {

class SetFuelEvent final: public IEvent {
public:
	SetFuelEvent(EntityID id, 
		double current, double max);
	~SetFuelEvent() override;

	EntityID getId() const;
	double getCurrent() const;
	double getMax() const;

private:
	const EntityID _id;
	const double _current;
	const double _max;
};

}

#endif // FIREFLY_SET_FUEL_EVENT_H
