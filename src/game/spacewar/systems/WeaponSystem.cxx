#include "WeaponSystem.h"

#include <firefly/Engine.h>
#include <firefly/Entity.h>
#include <firefly/EntityManager.h>
#include <firefly/EntityPrototypes.h>
#include <firefly/EventManager.h>

#include <firefly/components/Ammunition.h>
#include <firefly/components/Position.h>
#include <firefly/components/Velocity.h>
#include <firefly/components/Lifetime.h>

#include <firefly/events/ShootEvent.h>
#include <firefly/events/PositionEvent.h>
#include <firefly/events/SetSpeedEvent.h>
#include <firefly/events/AddSpeedEvent.h>
#include <firefly/events/SetAccelerationEvent.h>
#include <firefly/events/SetAmmunitionEvent.h>

#include "WeaponId.h"
#include "misc/VelocityHelpers.h"

namespace spacewar {

WeaponSystem::WeaponSystem(firefly::Engine* engine):
	firefly::ISystem(WeaponSystem::Name, engine) {

	addRequiredComponent(firefly::Ammunition::ComponentName);
	addRequiredComponent(firefly::Position::ComponentName);
	addRequiredComponent(firefly::Velocity::ComponentName);
}

WeaponSystem::~WeaponSystem() {
}

bool WeaponSystem::onEvent(
	const std::shared_ptr<firefly::IEvent>& event) {

	switch (event->getType()) {
	case firefly::EventType::Shoot: {
		const auto shootEvent = 
			static_cast<firefly::ShootEvent*>(event.get());
		if (!shootEvent) {
			return false;
		}

		auto entity = getEntity(shootEvent->getId());
		if (!entity) {
			return false;
		}

		shoot(entity,
			shootEvent->getWeaponId());
		return true;
	} break;

	case firefly::EventType::SetAmmunition: {
		const auto setAmmunitionEvent = 
			static_cast<firefly::SetAmmunitionEvent*>(event.get());
		if (!setAmmunitionEvent) {
			return false;
		}

		auto entity = getEntity(setAmmunitionEvent->getId());
		if (!entity) {
			return false;
		}

		reload(entity,
			setAmmunitionEvent->getWeaponId(),
			setAmmunitionEvent->getRounds());
		return true;
	} break;

	default:
		break;
	}

	return false;
}

void WeaponSystem::shoot(
	firefly::Entity* entity, int weaponId) const {

	if (!entity || weaponId < 0) {
		return;
	}

	const auto ammunitionComponent = 
		entity->getComponent<firefly::Ammunition>();
	const auto playerPosition = 
		entity->getComponent<firefly::Position>();
	const auto playerVelocity = 
		entity->getComponent<firefly::Velocity>();

	if (!ammunitionComponent || 
		!playerPosition || 
		!playerVelocity) {
		return;
	}

	if (ammunitionComponent->weapons.find(weaponId) == 
		ammunitionComponent->weapons.end()) {
		return;
	}

	auto& weapon = ammunitionComponent->weapons[weaponId];
	const auto timepoint = SDL_GetTicks64();
	const auto elapsedMs = timepoint - weapon.lastShotTimepoint;
	if (elapsedMs < weapon.cooldownTimeMs) {
		return;
	}

	if (weapon.maxRounds > 0) {
		if (weapon.rounds <= 0) {
			return;
		}

		weapon.rounds--;
	}

	weapon.lastShotTimepoint = timepoint;

	const auto entityPrototypes = getEngine()->getEntityPrototypes();

	auto projectile = entityPrototypes->makeEntity(
		weapon.projectile);
	if (!projectile) {
		return;
	}

	auto velocity = projectile->getComponent<firefly::Velocity>();
	auto position = projectile->getComponent<firefly::Position>();
	auto lifetime = projectile->getComponent<firefly::Lifetime>();
	if (!velocity || !position || !lifetime) {
		return;
	}

	lifetime->timepoint = timepoint;

	projectile->setActive(true);

	const auto entityManager = getEngine()->getEntityManager();
	entityManager->addEntity(projectile);

	// TODO configure it
	constexpr double spawnDistance = 30.0;

	double x = playerPosition->x;
	double y = playerPosition->y;

	movePoint(x, y, spawnDistance, 
		playerPosition->direction);

	const auto eventManager = getEngine()->getEventManager();
	std::shared_ptr<firefly::IEvent> event;

	event.reset(new firefly::SetSpeedEvent(
		projectile->getId(), velocity->speed, 
		playerPosition->direction));
	eventManager->registerEvent(std::move(event));

	event.reset(new firefly::AddSpeedEvent(
		projectile->getId(), playerVelocity->speed, 
		playerVelocity->speedDirection));
	eventManager->registerEvent(std::move(event));

	event.reset(new firefly::SetAccelerationEvent(
		projectile->getId(), velocity->acceleration, 
		playerPosition->direction, velocity->isConstantAcceleration));
	eventManager->registerEvent(std::move(event));

	event.reset(new firefly::PositionEvent(
		projectile->getId(), x, y, playerPosition->direction));
	eventManager->registerEvent(std::move(event));
}

void WeaponSystem::reload(firefly::Entity* entity, 
	int weaponId, int rounds) const {
	if (!entity || weaponId < 0) {
		return;
	}

	const auto ammunitionComponent = 
		entity->getComponent<firefly::Ammunition>();
	if (!ammunitionComponent) {
		return;
	}

	if (ammunitionComponent->weapons.find(weaponId) == 
		ammunitionComponent->weapons.end()) {
		return;
	}

	auto& weapon = ammunitionComponent->weapons[weaponId];
	weapon.rounds = rounds;
}

}
