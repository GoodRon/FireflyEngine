#include "AddSpeedEvent.h"

namespace firefly {

AddSpeedEvent::AddSpeedEvent(EntityID id,
	double speed, double direction):
	IEvent(EventType::AddSpeed),
	_id(id),
	_speed(speed),
	_direction(direction) {
}

AddSpeedEvent::~AddSpeedEvent() {
}

EntityID AddSpeedEvent::getId() const {
	return _id;
}

double AddSpeedEvent::getSpeed() const {
	return _speed;
}

double AddSpeedEvent::getDirection() const {
	return _direction;
}

}
