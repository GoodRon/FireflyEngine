#include "NativeEvent.h"

namespace firefly {

NativeEvent::NativeEvent(const SDL_Event& event):
	IEvent(EventType::Native),
	_event(event) {
}

NativeEvent::~NativeEvent() {
}

SDL_Event NativeEvent::getSDLEvent() const {
	return _event;
}

}
