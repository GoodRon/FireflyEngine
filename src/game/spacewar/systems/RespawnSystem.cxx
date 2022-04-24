#include "RespawnSystem.h"

#include <forward_list>
#include <random>

#include <SDL_timer.h>

#include <firefly/Engine.h>
#include <firefly/EntityManager.h>
#include <firefly/EventManager.h>
#include <firefly/Entity.h>
#include <firefly/Renderer.h>

#include <firefly/components/Lives.h>
#include <firefly/components/Position.h>
#include <firefly/components/Fuel.h>
#include <firefly/components/Ammunition.h>
#include <firefly/components/Player.h>

#include <firefly/events/KillEvent.h>
#include <firefly/events/StateEvent.h>
#include <firefly/events/SetSpeedEvent.h>
#include <firefly/events/PositionEvent.h>
#include <firefly/events/SetFuelEvent.h>
#include <firefly/events/SetAmmunitionEvent.h>
#include <firefly/events/GameStateEvent.h>

#include "ObjectStates.h"
#include "states/GameStates.h"

namespace spacewar {

// TODO move to helpers
static int randomInt(int min, int max) {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(min, max);

	return dist(mt);
}

static void randomScreenPosition(
	int width, int height, double& x, double& y) {

	x = static_cast<double>(randomInt(0, width));
	y = static_cast<double>(randomInt(0, height));
}

RespawnSystem::RespawnSystem(firefly::Engine* engine):
	firefly::ISystem(RespawnSystem::Name, engine),
	_entityManager(engine->getEntityManager()) {

	addRequiredComponent(firefly::Lives::ComponentName);
}

RespawnSystem::~RespawnSystem() {
}

bool RespawnSystem::onEvent(
	const std::shared_ptr<firefly::IEvent>& event) {

	switch (event->getType()) {
	case firefly::EventType::Kill: {
		const auto killEvent = 
			static_cast<firefly::KillEvent*>(event.get());
		if (!killEvent) {
			return false;
		}

		killEntity(killEvent->getId());
		return true;
	} break;

	default:
		break;
	}

	return false;
}

void RespawnSystem::killEntity(firefly::EntityID id) const {
	const auto entity = getEntity(id);
	if (!entity) {
		return;
	}

	const auto lives = entity->getComponent<firefly::Lives>();
	if (!lives) {
		_entityManager->removeEntity(id);
		return;
	}

	if (lives->maxLives == 0) {
		respawnEntity(id);
		return;
	}
	
	lives->currentLives--;
	if (lives->currentLives > 0) {
		respawnEntity(id);
		return;
	}

	_entityManager->removeEntity(id);

	const auto player = entity->getComponent<firefly::Player>();
	if (!player) {
		return;
	}
	
	std::shared_ptr<firefly::IEvent> event(
		new firefly::GameStateEvent(GameState::GameOver));

	const auto eventManager = getEngine()->getEventManager();
	eventManager->registerEvent(std::move(event));
}

void RespawnSystem::respawnEntity(firefly::EntityID id) const {
	const auto entity = getEntity(id);
	if (!entity) {
		return;
	}

	const auto position = entity->getComponent<firefly::Position>();
	if (!position) {
		return;
	}

	const auto renderer = getEngine()->getRenderer();
	const auto rect = renderer->getViewport();
	
	double x = 0;
	double y = 0;
	randomScreenPosition(rect.w, rect.h, x, y);

	const auto eventManager = getEngine()->getEventManager();

	std::shared_ptr<firefly::IEvent> event;

	event.reset(new firefly::SetSpeedEvent(
		entity->getId(), 0.0, 0.0));

	eventManager->registerEvent(std::move(event));

	event.reset(new firefly::PositionEvent(
		entity->getId(), x, y, position->direction));

	eventManager->registerEvent(std::move(event));
	
	event.reset(new firefly::StateEvent(
		entity->getId(), ObjectState::Idle));

	eventManager->registerEvent(std::move(event));

	const auto fuel = entity->getComponent<firefly::Fuel>();
	if (!fuel) {
		return;
	}

	event.reset(new firefly::SetFuelEvent(
		entity->getId(), fuel->max, fuel->max));

	eventManager->registerEvent(std::move(event));

	const auto ammunition = 
		entity->getComponent<firefly::Ammunition>();
	if (!ammunition) {
		return;
	}

	for (auto& weapon: ammunition->weapons) {
		event.reset(new firefly::SetAmmunitionEvent(
			entity->getId(), weapon.first, 
			weapon.second.maxRounds));

		eventManager->registerEvent(std::move(event));
	}

}

}
