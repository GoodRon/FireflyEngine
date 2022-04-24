/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_SHOOT_EVENT_H
#define FIREFLY_SHOOT_EVENT_H

#include "IEvent.h"
#include "Types.h"

namespace firefly {

class ShootEvent final: public IEvent {
public:
	ShootEvent(EntityID id, int weaponId);
	~ShootEvent() override;

	EntityID getId() const;
	int getWeaponId() const;

private:
	const EntityID _id;
	const int _weaponId;
};

}

#endif // FIREFLY_SHOOT_EVENT_H
