#include "SystemBuilder.h"

#include "systems/ShipControlSystem.h"
#include "systems/PositioningSystem.h"
#include "systems/GravitationalSystem.h"
#include "systems/StateSystem.h"
#include "systems/LifetimeSystem.h"
#include "systems/CollisionSystem.h"
#include "systems/VelocitySystem.h"
#include "systems/RespawnSystem.h"
#include "systems/PlayerUISystem.h"
#include "systems/FuelSystem.h"
#include "systems/WeaponSystem.h"

namespace spacewar {

// TODO improve it
std::shared_ptr<firefly::ISystem> buidSystem(
	const std::string& name,
	firefly::Engine* engine) {

	if (name == CollisionSystem::Name) {
		return std::shared_ptr<firefly::ISystem>(
			new CollisionSystem(engine));
	}

	if (name == GravitationalSystem::Name) {
		return std::shared_ptr<firefly::ISystem>(
			new GravitationalSystem(engine));
	}

	if (name == PositioningSystem::Name) {
		return std::shared_ptr<firefly::ISystem>(
			new PositioningSystem(engine));
	}

	if (name == LifetimeSystem::Name) {
		return std::shared_ptr<firefly::ISystem>(
			new LifetimeSystem(engine));
	}

	if (name == RespawnSystem::Name) {
		return std::shared_ptr<firefly::ISystem>(
			new RespawnSystem(engine));
	}

	if (name == ShipControlSystem::Name) {
		return std::shared_ptr<firefly::ISystem>(
			new ShipControlSystem(engine));
	}

	if (name == StateSystem::Name) {
		return std::shared_ptr<firefly::ISystem>(
			new StateSystem(engine));
	}

	if (name == VelocitySystem::Name) {
		return std::shared_ptr<firefly::ISystem>(
			new VelocitySystem(engine));
	}

	if (name == PlayerUISystem::Name) {
		return std::shared_ptr<firefly::ISystem>(
			new PlayerUISystem(engine));
	}

	if (name == FuelSystem::Name) {
		return std::shared_ptr<firefly::ISystem>(
			new FuelSystem(engine));
	}

	if (name == WeaponSystem::Name) {
		return std::shared_ptr<firefly::ISystem>(
			new WeaponSystem(engine));
	}

	return nullptr;
}

}
