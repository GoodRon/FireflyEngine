#include "SetAmmunitionEvent.h"

namespace firefly {

SetAmmunitionEvent::SetAmmunitionEvent(
	EntityID id, int weaponId, int rounds):
	IEvent(EventType::SetAmmunition),
	_id(id),
	_weaponId(weaponId),
	_rounds(rounds) {
}

SetAmmunitionEvent::~SetAmmunitionEvent() {
}

EntityID SetAmmunitionEvent::getId() const {
	return _id;
}

int SetAmmunitionEvent::getWeaponId() const {
	return _weaponId;
}

int SetAmmunitionEvent::getRounds() const {
	return _rounds;
}

}
