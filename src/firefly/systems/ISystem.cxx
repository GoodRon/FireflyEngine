#include "ISystem.h"

#include <SDL_timer.h>

#include "Entity.h"
#include "events/EntityEvent.h"
#include "components/IComponent.h"

namespace firefly {

ISystem::ISystem(const std::string& name, 
	Engine* engine): 
	_name(name), 
	_engine(engine),
	_isActive(false),
	_requiredComponents(),
	_entities(),
	_updateTimepoint(SDL_GetTicks64()) {
}
		
ISystem::~ISystem() {
}

const std::string ISystem::getName() const {
	return _name;
}

bool ISystem::processEvent(const std::shared_ptr<IEvent>& event) {
	if (!event) {
		return false;
	}

	switch (event->getType()) {
		case EventType::Entity: {
			auto entityEvent = static_cast<EntityEvent*>(event.get());
			if (!entityEvent) {
				return false;
			}

			auto entity = entityEvent->getEntity();
			if (!entity) {
				return false;
			}

			if (entityEvent->isRemoved()) {
				unregisterEntity(entity->getId());
				return false;
			}

			registerEntity(entity.get());
			return false;
		} break;

		case EventType::Update: {
			onUpdate();
			_updateTimepoint = SDL_GetTicks64();
			return false;
		} break;

		default:
			break;
	}

	return onEvent(event);
}

bool ISystem::onEvent(
		const std::shared_ptr<IEvent>&) {
	return false;
}

void ISystem::setActive(bool isActive) {
	_isActive = isActive;
	if (_isActive) {
		_updateTimepoint = SDL_GetTicks64();
	}
}

bool ISystem::isActive() const {
	return _isActive;
}

void ISystem::addRequiredComponent(const std::string& name) {
	_requiredComponents.insert(name);
}

bool ISystem::checkComponents(Entity* entity) const {
	if (!entity) {
		return false;
	}

	IComponent* component = nullptr;

	for (auto& componentName: _requiredComponents) {
		component = entity->getComponent(componentName);
		if (!component) {
			return false;
		}
	}
	return true;
}

Engine* ISystem::getEngine() const {
	return _engine;
}

const std::unordered_map<EntityID, Entity*>& 
ISystem::getEntities() const {
	return _entities;
}

uint64_t ISystem::getElapsedMs() const {
	return SDL_GetTicks64() - _updateTimepoint;
}

uint64_t ISystem::getLastUpdateTimepoint() const {
	return _updateTimepoint;
}

void ISystem::onUpdate() {
}

bool ISystem::onRegisterEntity(Entity*) {
	return true;
}

void ISystem::onUnregisterEntity(Entity*) {
}

Entity* ISystem::getEntity(EntityID id) const {
	auto it = _entities.find(id);
	if (it == _entities.end()) {
		return nullptr;
	}
	return it->second;
}

bool ISystem::registerEntity(Entity* entity) {
	if (!entity) {
		return false;
	}

	if (!checkComponents(entity)) {
		return false;
	}

	const auto id = entity->getId();
	bool result = true;

	if (_entities.find(id) == _entities.end()) {
		if (onRegisterEntity(entity)) {
			_entities[id] = entity;
		} else {
			result = false;
		}
	}
	return result;
}

void ISystem::unregisterEntity(EntityID id) {
	auto it = _entities.find(id);
	if (it != _entities.end()) {
		onUnregisterEntity((*it).second);
		_entities.erase(id);
	}
}

}
