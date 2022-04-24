#include "LifetimeSystem.h"

#include <SDL_timer.h>

#include <firefly/Engine.h>
#include <firefly/Entity.h>
#include <firefly/EventManager.h>
#include <firefly/components/Lifetime.h>
#include <firefly/events/StateEvent.h>

#include "ObjectStates.h"

namespace spacewar {

LifetimeSystem::LifetimeSystem(firefly::Engine* engine):
	firefly::ISystem(LifetimeSystem::Name, engine) {

	addRequiredComponent(firefly::Lifetime::ComponentName);
}

LifetimeSystem::~LifetimeSystem() {
}

void LifetimeSystem::onUpdate() {
	const auto eventManager = getEngine()->getEventManager();
	std::shared_ptr<firefly::IEvent> event;

	for (auto& entity: getEntities()) {
		if (!entity.second->isActive()) {
			continue;
		}

		if (isEntityExpired(entity.second)) {
			event.reset(new firefly::StateEvent(
				entity.second->getId(), ObjectState::Exploading));
			eventManager->registerEvent(std::move(event));
		}
	}

}

bool LifetimeSystem::isEntityExpired(firefly::Entity* entity) const {
	const auto lifetime = entity->getComponent<firefly::Lifetime>();
	if (!lifetime) {
		return true;
	}

	if (SDL_GetTicks64() - lifetime->timepoint > lifetime->lifetimeMs) {
		return true;
	}
	return false;
}

}
