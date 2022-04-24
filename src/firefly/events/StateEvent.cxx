#include "StateEvent.h"

namespace firefly {

StateEvent::StateEvent(EntityID id, int state):
	IEvent(EventType::State),
	_id(id),
	_state(state) {
}

StateEvent::~StateEvent() {
}

EntityID StateEvent::getId() const {
	return _id;
}

int StateEvent::getState() const {
	return _state;
}

}
