#include "CollisionEvent.h"

namespace firefly {

CollisionEvent::CollisionEvent(EntityID id):
	IEvent(EventType::Collision),
	_id(id) {
}

CollisionEvent::~CollisionEvent() {
}

EntityID CollisionEvent::getId() const {
	return _id;
}

}
