#include "EntityPrototypes.h"

#include "Entity.h"

#include "components/IComponent.h"

namespace firefly {

EntityPrototypes::EntityPrototypes():
	_prototypes() {
}

bool EntityPrototypes::registerPrototype(
	const std::string& name,
	const std::shared_ptr<Entity>& prototype) {

	if (!prototype) {
		return false;
	}

	if (hasPrototype(name)) {
		return false;
	}

	std::unique_ptr<Entity> ptr(new Entity(*prototype.get()));
	_prototypes[name] = std::move(ptr);
	return true;
}

void EntityPrototypes::removePrototype(const std::string& name) {
	if (!hasPrototype(name)) {
		return;
	}

	_prototypes.erase(name);
}

bool EntityPrototypes::hasPrototype(const std::string& name) const {
	if (_prototypes.find(name) == _prototypes.end()) {
		return false;
	}
	return true;
}

std::shared_ptr<Entity> EntityPrototypes::makeEntity(
	const std::string& name) const {
	if (!hasPrototype(name)) {
		return nullptr;
	}

	std::shared_ptr<Entity> entity(new Entity(name));
	(*entity.get()) = (*_prototypes.at(name).get());

	return entity;
}

void EntityPrototypes::clear() {
	_prototypes.clear();
}

}
