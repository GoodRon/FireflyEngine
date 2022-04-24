#include "IGameState.h"

#include "Engine.h"
#include "Entity.h"
#include "EntityManager.h"
#include "SystemManager.h"

#include "systems/ISystem.h"
#include "events/EntityEvent.h"
#include "events/SystemEvent.h"

namespace firefly {

IGameState::IGameState(
	Engine* engine, 
	int id):
	_engine(engine),
	_id(id),
	_isInit(false),
	_objectIds(),
	_systemNames() {
}

IGameState::~IGameState() {
	deinit();
}

int IGameState::getId() const {
	return _id;
}

void IGameState::init() {
	if (_isInit) {
		return;
	}

	buildSystems();
	buildObjects();
	
	_isInit = true;
}

void IGameState::deinit() {
	if (!_isInit) {
		return;
	}

	destroySystems();
	destroyObjects();
	_isInit = false;
}

bool IGameState::isInit() const {
	return _isInit;
}

void IGameState::onEnter() {
}

void IGameState::onExit() {
}

bool IGameState::processEvent(
	const std::shared_ptr<IEvent>& event) {

	if (!event) {
		return false;
	}

	switch (event->getType()) {
	case EventType::Entity: {
		auto entityEvent = static_cast<EntityEvent*>(event.get());
		if (!entityEvent) {
			break;
		}

		auto entity = entityEvent->getEntity();
		if (!entity) {
			break;
		}

		if (entityEvent->isRemoved()) {
			_objectIds.erase(entity->getId());
		} else {
			_objectIds.insert(entity->getId());
		}
		
	} break;

	case EventType::System: {
		auto systemEvent = static_cast<SystemEvent*>(event.get());
		if (!systemEvent) {
			break;
		}

		if (systemEvent->isRemoved()) {
			_systemNames.erase(systemEvent->getSystemName());
			break;
		}
		
		if (systemEvent->isRemoved()) {
			_systemNames.erase(systemEvent->getSystemName());
		} else {
			_systemNames.insert(systemEvent->getSystemName());
		}
		
	} break;

	default:
		break;
	}
	
	if (onEvent(event)) {
		return true;
	}

	const auto systemManager = getEngine()->getSystemManager();
	return systemManager->processEvent(event);
}

bool IGameState::onEvent(
	const std::shared_ptr<IEvent>& event) {
	return false;
}

Engine* IGameState::getEngine() const {
	return _engine;
}

void IGameState::buildObjects() {
}

void IGameState::setObjectIds(
	std::unordered_set<EntityID>&& ids) {
	_objectIds = std::move(ids);
}

void IGameState::destroyObjects() {
	const auto engine = getEngine();
	const auto entityManager = engine->getEntityManager();

	for (auto& id: _objectIds) {
		entityManager->removeEntity(id);
	}
	_objectIds.clear();
}

void IGameState::setObjectsActive(bool isActive) const {
	const auto engine = getEngine();
	const auto entityManager = engine->getEntityManager();

	std::shared_ptr<Entity> entity;
	for (auto& id: _objectIds) {
		entity = std::move(entityManager->getEntity(id));
		if (!entity) {
			continue;
		}
		entity->setActive(isActive);
	}
}

void IGameState::setSystemNames(
	std::unordered_set<std::string>&& systemNames) {
	_systemNames = std::move(systemNames);
}

void IGameState::buildSystems() {
}

void IGameState::destroySystems() {
	const auto engine = getEngine();
	const auto systemManager = engine->getSystemManager();

	for (auto& systemName: _systemNames) {
		systemManager->removeSystem(systemName);
	}
	_systemNames.clear();
}

void IGameState::setSystemsActive(bool isActive) const {
	const auto engine = getEngine();
	const auto systemManager = engine->getSystemManager();

	std::shared_ptr<ISystem> sys;
	for (auto& systemName: _systemNames) {
		sys = std::move(systemManager->getSystem(systemName));
		if (sys) {
			sys->setActive(isActive);
		}
	}
}

}
