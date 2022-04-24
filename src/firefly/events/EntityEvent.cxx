#include "EntityEvent.h"

namespace firefly {

EntityEvent::EntityEvent(
	const std::shared_ptr<Entity>& entity,
	bool isRemoved):
	IEvent(EventType::Entity),
	_entity(entity),
	_isRemoved(isRemoved) {
}

EntityEvent::~EntityEvent() {
}

std::shared_ptr<Entity> 
EntityEvent::getEntity() const {
	return _entity;
}

bool EntityEvent::isRemoved() const {
	return _isRemoved;
}

}