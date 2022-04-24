#include "SystemEvent.h"

namespace firefly {

SystemEvent::SystemEvent(
	const std::string& systemName,
	bool isRemoved):
	IEvent(EventType::System),
	_systemName(systemName),
	_isRemoved(isRemoved) {
}

SystemEvent::~SystemEvent() {
}

std::string SystemEvent::getSystemName() const {
	return _systemName;
}

bool SystemEvent::isRemoved() const {
	return _isRemoved;
}

};
