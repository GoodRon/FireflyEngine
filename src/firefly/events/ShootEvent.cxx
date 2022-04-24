#include "ShootEvent.h"

namespace firefly {

ShootEvent::ShootEvent(EntityID id, int weaponId):
	IEvent(EventType::Shoot),
	_id(id),
	_weaponId(weaponId) {
}

ShootEvent::~ShootEvent() {
}

EntityID ShootEvent::getId() const {
	return _id;
}

int ShootEvent::getWeaponId() const {
	return _weaponId;
}

}
