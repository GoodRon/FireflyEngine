#include "PositioningSystem.h"

#include <SDL_timer.h>

#include <firefly/Engine.h>
#include <firefly/Renderer.h>
#include <firefly/Entity.h>

#include <firefly/components/Position.h>
#include <firefly/components/Velocity.h>

#include <firefly/events/PositionEvent.h>

namespace spacewar {

PositioningSystem::PositioningSystem(firefly::Engine* engine):
	firefly::ISystem(PositioningSystem::Name, engine) {

	addRequiredComponent(firefly::Position::ComponentName);
	addRequiredComponent(firefly::Velocity::ComponentName);
}

PositioningSystem::~PositioningSystem() {
}

bool PositioningSystem::onEvent(
	const std::shared_ptr<firefly::IEvent>& event) {

	switch (event->getType()) {
	case firefly::EventType::Position: {
		const auto positionEvent = 
			static_cast<firefly::PositionEvent*>(event.get());
		if (!positionEvent) {
			return false;
		}

		updatePosition(positionEvent->getId(),
			positionEvent->getX(), positionEvent->getY(),
			positionEvent->getDirection());
		return true;
	} break;

	default:
		break;
	}

	return false;
}

void PositioningSystem::onUpdate() {
	firefly::Position* position = nullptr;
	firefly::Velocity* velocity = nullptr;

	for (auto& entity: getEntities()) {
		if (!entity.second->isActive()) {
			continue;
		}

		position = entity.second->getComponent<firefly::Position>();
		velocity = entity.second->getComponent<firefly::Velocity>();

		if (!position || !velocity){
			continue;
		}

		processPosition(position, velocity);
	}
}

void PositioningSystem::updatePosition(firefly::EntityID id,
	double x, double y, double direction) const {

	const auto entity = getEntity(id);
	if (!entity) {
		return;
	}

	const auto position = entity->getComponent<firefly::Position>();
	if (!position) {
		return;
	}

	position->x = x;
	position->y = y;
	position->direction = direction;

	const auto velocity = entity->getComponent<firefly::Velocity>();
	if (!velocity) {
		return;
	}
	processPosition(position, velocity);
}

void PositioningSystem::processPosition(
		firefly::Position* position, firefly::Velocity* velocity) const {
	
	if (!position || !velocity) {
		return;
	}

	if (!velocity->isActive) {
		return;
	}

	const auto elapsedMs = getElapsedMs();

	position->x += velocity->speedX * elapsedMs / 1000.0;
	position->y += velocity->speedY * elapsedMs / 1000.0;

	wrapCoordinates(position);
}

void PositioningSystem::wrapCoordinates(
		firefly::Position* position) const {
	if (!position) {
		return;
	}

	const auto renderer = getEngine()->getRenderer();
	SDL_Rect windowRect = renderer->getViewport();

	if ((position->x + position->centerX) > (windowRect.w + position->width)) {
		position->x = -position->width;
	}

	if ((position->x + position->centerX) < (-position->width)) {
		position->x = windowRect.w;
	}

	if ((position->y + position->centerY) > (windowRect.h + position->height)) {
		position->y = -position->height;
	}

	if ((position->y + position->centerY) < (-position->height)) {
		position->y = windowRect.h;
	}
}

}
