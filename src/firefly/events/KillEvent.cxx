#include "KillEvent.h"

namespace firefly {

KillEvent::KillEvent(EntityID id):
	IEvent(EventType::Kill),
	_id(id) {
}

KillEvent::~KillEvent() {
}

EntityID KillEvent::getId() const {
	return _id;
}

}
