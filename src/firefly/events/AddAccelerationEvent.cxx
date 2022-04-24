#include "AddAccelerationEvent.h"

namespace firefly {

AddAccelerationEvent::AddAccelerationEvent(EntityID id,
	double acceleration, double direction):
	IEvent(EventType::AddAcceleration),
	_id(id),
	_acceleration(acceleration),
	_direction(direction) {
}

AddAccelerationEvent::~AddAccelerationEvent() {
}

EntityID AddAccelerationEvent::getId() const {
	return _id;
}

double AddAccelerationEvent::getAcceleration() const {
	return _acceleration;
}

double AddAccelerationEvent::getDirection() const {
	return _direction;
}

}
