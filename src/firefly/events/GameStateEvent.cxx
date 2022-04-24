#include "GameStateEvent.h"

namespace firefly {

GameStateEvent::GameStateEvent(int state):
	IEvent(EventType::GameState),
	_state(state) {
}

GameStateEvent::~GameStateEvent() {
}

int GameStateEvent::getState() const {
	return _state;
}

}
