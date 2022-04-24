#include "UpdateEvent.h"

namespace firefly {

UpdateEvent::UpdateEvent():
	IEvent(EventType::Update) {
}

UpdateEvent::~UpdateEvent() {
}


}