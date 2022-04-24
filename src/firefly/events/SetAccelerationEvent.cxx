#include "SetAccelerationEvent.h"

namespace firefly {

SetAccelerationEvent::SetAccelerationEvent(EntityID id,
	double acceleration, double direction, bool isConstant):
	IEvent(EventType::SetAcceleration),
	_id(id),
	_acceleration(acceleration),
	_direction(direction),
	_isConstant(isConstant) {
}

SetAccelerationEvent::~SetAccelerationEvent() {
}

EntityID SetAccelerationEvent::getId() const {
	return _id;
}

double SetAccelerationEvent::getAcceleration() const {
	return _acceleration;
}

double SetAccelerationEvent::getDirection() const {
	return _direction;
}

bool SetAccelerationEvent::isConstant() const {
	return _isConstant;
}

}
