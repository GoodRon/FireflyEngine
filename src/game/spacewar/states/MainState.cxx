#include "MainState.h"

#include "GameStates.h"

#include <firefly/Engine.h>
#include <firefly/Renderer.h>
#include <firefly/EntityPrototypes.h>
#include <firefly/EntityManager.h>
#include <firefly/SystemManager.h>
#include <firefly/Entity.h>

#include <firefly/systems/ISystem.h>
#include <firefly/events/NativeEvent.h>
#include <firefly/components/ShipControls.h>
#include <firefly/components/Position.h>

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

static void setControls(firefly::Entity* entity,
	int keyCodeUp, int keyCodeDown, 
	int keyCodeLeft, int keyCodeRight) {

	if (!entity) {
		return;
	}

	const auto controls = 
		entity->getComponent<firefly::ShipControls>();
	if (!controls) {
		return;
	}

	controls->keyCodeUp = keyCodeUp;
	controls->keyCodeDown = keyCodeDown;
	controls->keyCodeLeft = keyCodeLeft;
	controls->keyCodeRight = keyCodeRight;
}

static void setPosition(firefly::Entity* entity,
	double x, double y) {

	if (!entity) {
		return;
	}

	const auto position = 
		entity->getComponent<firefly::Position>();
	if (!position) {
		return;
	}

	position->x = x;
	position->y = y;
}

MainState::MainState(firefly::Engine* engine):
	firefly::IGameState(engine, GameState::Main) {
}

MainState::~MainState() {
}

void MainState::onEnter() {
	if (!isInit()) {
		return;
	}

	constexpr bool isActive = true;
	setObjectsActive(isActive);
	setSystemsActive(isActive);
}

void MainState::onExit() {
	if (!isInit()) {
		return;
	}

	constexpr bool isActive = false;
	setObjectsActive(isActive);
	setSystemsActive(isActive);
}

bool MainState::onEvent(
	const std::shared_ptr<firefly::IEvent>& event) {

	if (!isInit()) {
		return false;
	}

	if (!isInit()) {
		return false;
	}

	if (event->getType() != firefly::EventType::Native) {
		return false;
	}

	const auto nativeEvent = 
		static_cast<firefly::NativeEvent*>(event.get());

	const auto sdlEvent = nativeEvent->getSDLEvent();
	if (sdlEvent.type == SDL_KEYDOWN && 
		sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
		// NOTE exit the game
		getEngine()->stop();
		return true;
	}

	return false;
}

void MainState::buildObjects() {
	const auto engine = getEngine();
	const auto entityManager = engine->getEntityManager();
	const auto prototypes = engine->getEntityPrototypes();

	// TODO read form a config
	const std::unordered_set<std::string> entityNames{
		"Player_1", "Player_2", "Star", "Background"
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

		configureEntity(entity.get());

		entityManager->addEntity(std::move(entity));
	}

	setObjectIds(std::move(ids));
}

void MainState::buildSystems() {
	const auto engine = getEngine();
	const auto systemManager = engine->getSystemManager();

	// TODO read form a config
	std::unordered_set<std::string> systemNames{
		VelocitySystem::Name,
		PositioningSystem::Name,
		CollisionSystem::Name,
		LifetimeSystem::Name,
		RespawnSystem::Name,
		StateSystem::Name,
		FuelSystem::Name,
		GravitationalSystem::Name,
		ShipControlSystem::Name,
		WeaponSystem::Name,
		PlayerUISystem::Name
	};

	std::shared_ptr<firefly::ISystem> system;
	for (auto& name: systemNames) {
		system = std::move(buidSystem(name, engine));
		systemManager->addSystem(std::move(system));
	}

	setSystemNames(std::move(systemNames));
}

void MainState::configureEntity(
	firefly::Entity* entity) const {

	// TODO improve

	const auto renderer = getEngine()->getRenderer();
	const auto viewport = renderer->getViewport();

	constexpr double spawnX = 140.0;
	constexpr double spawnY = 140.0;

	const auto name = entity->getName();

	if (name == "Player_1") {
		setControls(entity, SDLK_w, SDLK_s,
			SDLK_a, SDLK_d);

		setPosition(entity, spawnX, spawnY);
		return;
	}

	if (name == "Player_2") {
		setControls(entity, SDLK_KP_8, SDLK_KP_5,
			SDLK_KP_4, SDLK_KP_6);

		setPosition(entity, 
			viewport.w - spawnX, viewport.h - spawnY);
		return;
	}

	if (name == "Star") {
		setPosition(entity, 
			viewport.w / 2.0, viewport.h / 2.0);
		return;
	}
}

}
