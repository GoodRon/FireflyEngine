#include "PositionEvent.h"

namespace firefly {

PositionEvent::PositionEvent(EntityID id,
	double x, double y, double direction):
	IEvent(EventType::Position),
	_id(id),
	_x(x),
	_y(y),
	_direction(direction) {
}

PositionEvent::~PositionEvent() {
}

EntityID PositionEvent::getId() const {
	return _id;
}

double PositionEvent::getX() const {
	return _x;
}

double PositionEvent::getY() const {
	return _y;
}

double PositionEvent::getDirection() const {
	return _direction;
}

}
