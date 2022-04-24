#include "SetFuelEvent.h"

namespace firefly {

SetFuelEvent::SetFuelEvent(
	EntityID id, double current, double max):
	IEvent(EventType::SetFuel),
	_id(id),
	_current(current),
	_max(max) {
}

SetFuelEvent::~SetFuelEvent() {
}

EntityID SetFuelEvent::getId() const {
	return _id;
}

double SetFuelEvent::getCurrent() const {
	return _current;
}

double SetFuelEvent::getMax() const {
	return _max;
}

}
