#include "SetSpeedEvent.h"

namespace firefly {

SetSpeedEvent::SetSpeedEvent(EntityID id,
	double speed, double direction):
	IEvent(EventType::SetSpeed),
	_id(id),
	_speed(speed),
	_direction(direction) {
}

SetSpeedEvent::~SetSpeedEvent() {
}

EntityID SetSpeedEvent::getId() const {
	return _id;
}

double SetSpeedEvent::getSpeed() const {
	return _speed;
}

double SetSpeedEvent::getDirection() const {
	return _direction;
}

}
