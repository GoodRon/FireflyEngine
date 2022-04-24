#include "MenuState.h"

#include "GameStates.h"

#include <firefly/Engine.h>
#include <firefly/EntityPrototypes.h>
#include <firefly/EntityManager.h>
#include <firefly/StateMachine.h>
#include <firefly/Entity.h>

#include <firefly/events/NativeEvent.h>

#include "SystemBuilder.h"

namespace spacewar {

MenuState::MenuState(firefly::Engine* engine):
	firefly::IGameState(engine, GameState::Menu) {
}

MenuState::~MenuState() {
}

void MenuState::onEnter() {
	if (!isInit()) {
		return;
	}
	setObjectsActive(true);
}

void MenuState::onExit() {
	if (!isInit()) {
		return;
	}
	setObjectsActive(false);
}

bool MenuState::onEvent(
	const std::shared_ptr<firefly::IEvent>& event) {

	if (!isInit()) {
		return false;
	}

	if (!event) {
		return false;
	}

	if (event->getType() != firefly::EventType::Native) {
		return false;
	}

	const auto nativeEvent = 
			static_cast<firefly::NativeEvent*>(event.get());

	const auto sdlEvent = nativeEvent->getSDLEvent();

	switch (sdlEvent.type) {
	case SDL_KEYDOWN: {
		if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
			getEngine()->stop();
			return true;
		}

		const auto engine = getEngine();
		const auto stateMachine = engine->getStateMachine();
		stateMachine->switchState(GameState::Main);
		return true;
	} break;

	default:
		break;
	}

	return false;
}

void MenuState::buildObjects() {
	const auto engine = getEngine();
	const auto entityManager = engine->getEntityManager();
	const auto prototypes = engine->getEntityPrototypes();

	// TODO read form a config
	const std::unordered_set<std::string> entityNames{
		"Logo"
	};
	std::unordered_set<firefly::EntityID> ids;

	std::shared_ptr<firefly::Entity> entity;
	for (auto& name: entityNames) {
		entity = std::move(prototypes->makeEntity(name));
		if (!entity) {
			continue;
		}

		entity->setActive(false);
		ids.insert(entity->getId());

		entityManager->addEntity(std::move(entity));
	}

	setObjectIds(std::move(ids));
}

}
