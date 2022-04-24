/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_SET_AMMUNITION_EVENT_H
#define FIREFLY_SET_AMMUNITION_EVENT_H

#include "IEvent.h"
#include "Types.h"

namespace firefly {

class SetAmmunitionEvent final: public IEvent {
public:
	SetAmmunitionEvent(EntityID id, 
		int weaponId, int rounds);
	~SetAmmunitionEvent() override;

	EntityID getId() const;
	int getWeaponId() const;
	int getRounds() const;

private:
	const EntityID _id;
	const double _weaponId;
	const double _rounds;
};

}

#endif // FIREFLY_SET_AMMUNITION_EVENT_H
