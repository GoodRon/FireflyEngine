#include "StateSystem.h"

#include <SDL_timer.h>
#include <random>

#include <firefly/Engine.h>
#include <firefly/Renderer.h>
#include <firefly/Entity.h>
#include <firefly/EventManager.h>

#include <firefly/events/StateEvent.h>
#include <firefly/events/KillEvent.h>
#include <firefly/events/PositionEvent.h>
#include <firefly/events/CollisionEvent.h>
#include <firefly/events/SetSpeedEvent.h>

#include <firefly/components/State.h>
#include <firefly/components/Position.h>
#include <firefly/components/Visual.h>
#include <firefly/components/Velocity.h>
#include <firefly/components/Gravity.h>
#include <firefly/components/Lives.h>
#include <firefly/components/Hyperspace.h>
#include <firefly/components/RoundCollidable.h>

#include "ObjectStates.h"

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

static void setEntityReactiveness(
	firefly::Entity* entity, bool isReactive) {

	const auto velocity = entity->getComponent<firefly::Velocity>();
	if (velocity) {
		velocity->isActive = isReactive;
	}

	const auto gravity = entity->getComponent<firefly::Gravity>();
	if (gravity) {
		gravity->isActive = isReactive;
	}

	const auto collidable = entity->getComponent<firefly::RoundCollidable>();
	if (collidable) {
		collidable->isActive = isReactive;
	}
}

StateSystem::StateSystem(firefly::Engine* engine):
	firefly::ISystem(StateSystem::Name, engine) {

	addRequiredComponent(firefly::State::ComponentName);
	addRequiredComponent(firefly::Position::ComponentName);
	addRequiredComponent(firefly::Visual::ComponentName);
	addRequiredComponent(firefly::Velocity::ComponentName);
}

StateSystem::~StateSystem() {
}

bool StateSystem::onEvent(
		const std::shared_ptr<firefly::IEvent>& event) {

	switch (event->getType()) {
	case firefly::EventType::Collision: {
		const auto collisionEvent = 
			static_cast<firefly::CollisionEvent*>(event.get());

		if (!collisionEvent) {
			return false;
		}

		const auto entity = getEntity(collisionEvent->getId());
		if (!entity) {
			return false;
		}

		switchState(entity, ObjectState::Exploading);
		return true;
	} break;

	case firefly::EventType::State: {
		const auto stateEvent = 
			static_cast<firefly::StateEvent*>(event.get());

		if (!stateEvent) {
			return false;
		}

		const auto entityId = stateEvent->getId();
		const auto state = stateEvent->getState();

		const auto entity = getEntity(entityId);
		if (!entity) {
			return false;
		}

		switchState(entity, state);
		return true;
	} break;

	default:
		break;
	}

	return false;
}

void StateSystem::onUpdate() {
	for (auto& entity: getEntities()) {
		if (!entity.second->isActive()) {
			continue;
		}

		updateState(entity.second);
	}
}

void StateSystem::updateState(
	firefly::Entity* entity) const {

	if (!entity) {
		return;
	}

	const auto stateComponent = entity->getComponent<firefly::State>();

	switch (stateComponent->current) {
	case ObjectState::Hyperspace:
		updateHyperspace(entity);
		break;

	case ObjectState::Exploading:
		updateExploading(entity);
		break;

	default:
		break;
	}
}

void StateSystem::switchState(
	firefly::Entity* entity, int state) const {

	const auto stateComponent = entity->getComponent<firefly::State>();
	const auto visualComponent = entity->getComponent<firefly::Visual>();
	const auto hyperspaceComponent = entity->getComponent<firefly::Hyperspace>();
	if (!stateComponent || !visualComponent) {
		return;
	}

	if (stateComponent->current == state) {
		return;
	}

	if (state == ObjectState::Hyperspace && !hyperspaceComponent) {
		return;
	}

	const uint64_t timepoint = SDL_GetTicks64();

	if (visualComponent->hasState(stateComponent->current)) {
		visualComponent->states[stateComponent->current].isFinished = false;
	}
	
	visualComponent->currentState = state;
	visualComponent->timepoint = timepoint;
	visualComponent->frameIndex = 0;

	if (visualComponent->hasState(state)) {
		visualComponent->states[state].isFinished = false;
	}

	stateComponent->previous = stateComponent->current;
	stateComponent->current = state;
	stateComponent->timepoint = timepoint;

	switch (state) {
	case ObjectState::Destroyed:
		setEntityReactiveness(entity, false);
		visualComponent->isVisible = false;
		break;

	case ObjectState::Hyperspace:
		setEntityReactiveness(entity, false);
		visualComponent->isVisible = false;
		break;

	case ObjectState::Exploading:
		setEntityReactiveness(entity, false);
		visualComponent->isVisible = true;
		break;
		
	default:
		setEntityReactiveness(entity, true);
		visualComponent->isVisible = true;
		break;
	}
}

void StateSystem::updateHyperspace(
	firefly::Entity* entity) const {

	if (!entity) {
		return;
	}

	const auto state = entity->getComponent<firefly::State>();
	const auto position = entity->getComponent<firefly::Position>();
	const auto hyperspace = entity->getComponent<firefly::Hyperspace>();
	if (!state || !position || !hyperspace) {
		return;
	}

	const auto timepoint = SDL_GetTicks64();

	if ((timepoint - state->timepoint) 
		< hyperspace->hyperspaceTimeMs) {
		// NOTE we are still in hyperspace
		return;
	}

	const auto eventManager = getEngine()->getEventManager();
	std::shared_ptr<firefly::IEvent> event;

	hyperspace->timepoint = timepoint;

	if (hyperspace->chanceOfMulfunction > 0) {
		if (randomInt(0, 100) <= hyperspace->chanceOfMulfunction) {
			event.reset(new firefly::StateEvent(
				entity->getId(), ObjectState::Exploading));
			eventManager->registerEvent(std::move(event));
			return;
		}
	}

	const auto renderer = getEngine()->getRenderer();
	const auto rect = renderer->getViewport();

	double x = 0;
	double y = 0;
	randomScreenPosition(rect.w, rect.h, x, y);

	event.reset(new firefly::SetSpeedEvent(
		entity->getId(), 0.0, 0.0));
	eventManager->registerEvent(std::move(event));

	event.reset(new firefly::PositionEvent(
		entity->getId(), x, y, position->direction));
	eventManager->registerEvent(std::move(event));

	event.reset(new firefly::StateEvent(
		entity->getId(), ObjectState::Idle));
	eventManager->registerEvent(std::move(event));
}

void StateSystem::updateExploading(
	firefly::Entity* entity) const {

	if (!entity) {
		return;
	}

	const auto visual = entity->getComponent<firefly::Visual>();
	if (visual) {
		// NOTE awaiting the animation to stop
		// TODO better wait for the state timeout
		if (visual->states[ObjectState::Exploading].isFinished == false) {
			return;
		}
	}

	const auto eventManager = getEngine()->getEventManager();

	std::shared_ptr<firefly::IEvent> event(new firefly::KillEvent(
		entity->getId()));
	eventManager->registerEvent(std::move(event));

	event.reset(new firefly::StateEvent(
		entity->getId(), ObjectState::Destroyed));
	eventManager->registerEvent(std::move(event));
}

}