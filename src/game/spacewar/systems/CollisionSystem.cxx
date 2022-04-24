#include "CollisionSystem.h"

#include <firefly/Engine.h>
#include <firefly/Entity.h>
#include <firefly/EventManager.h>
#include <firefly/Renderer.h>
#include <firefly/events/CollisionEvent.h>
#include <firefly/components/RoundCollidable.h>
#include <firefly/components/Position.h>

#include "misc/Quadtree.h"

namespace spacewar {

CollisionSystem::CollisionSystem(firefly::Engine* engine):
	firefly::ISystem(CollisionSystem::Name, engine),
	_qauadtree() {

	addRequiredComponent(firefly::RoundCollidable::ComponentName);
	addRequiredComponent(firefly::Position::ComponentName);

	auto renderer = engine->getRenderer();
	_qauadtree.reset(new EntityQuadtree(renderer->getViewport()));
}

CollisionSystem::~CollisionSystem() {
}

void CollisionSystem::onUpdate() {

	auto& entities = getEntities();
	if (entities.empty()) {
		return;
	}

	_qauadtree->clear();

	for (auto& entity: entities) {
		if (!entity.second->isActive()) {
			continue;
		}

		const auto collidable = entity.second->getComponent<firefly::RoundCollidable>();
		if (collidable->isActive) {
			_qauadtree->insert(entity.second);
		}
	}

	const auto eventManager = getEngine()->getEventManager();

	for (auto& entityIt: entities) {
		auto entity = entityIt.second;
		if (!entity->isActive()) {
			continue;
		}

		auto positionLeft = entity->getComponent<firefly::Position>();
		auto collidableLeft = entity->getComponent<firefly::RoundCollidable>();

		if (!collidableLeft->isActive) {
			continue;
		}

		auto nearestEntities = _qauadtree->retrieve(positionLeft->toRect());
		for (auto& nearestEntity: nearestEntities) {
			if (entity == nearestEntity) {
				continue;
			}

			auto positionRight = nearestEntity->getComponent<firefly::Position>();
			auto collidableRight = nearestEntity->getComponent<firefly::RoundCollidable>();

			if (isCollided(collidableLeft, positionLeft,
				collidableRight, positionRight)) {

				if (collidableRight->isDestructable) {
					std::shared_ptr<firefly::IEvent> event(new firefly::CollisionEvent(
						nearestEntity->getId()));
					
					eventManager->registerEvent(std::move(event));
				}
			}
		}
	}
}

bool CollisionSystem::isCollided(
		firefly::RoundCollidable* collidableLeft,
		firefly::Position* positionLeft,
		firefly::RoundCollidable* collidableRight,
		firefly::Position* positionRigth) const {

	if (!collidableLeft || !positionLeft ||
		!collidableRight || !positionRigth) {
		return false;
	}

	const auto centerLeft = positionLeft->center();
	const auto centerRight = positionRigth->center();

	const double distanceX = (positionLeft->x + centerLeft.x) -
		(positionRigth->x + centerRight.x);
	const double dsistanceY = (positionLeft->y + centerLeft.y) -
		(positionRigth->y + centerRight.y);
	const double squaredDistance = distanceX * distanceX 
		+ dsistanceY * dsistanceY;
	const double minCollisionDistance = collidableLeft->collidableRadius 
		+ collidableRight->collidableRadius;

	if (squaredDistance < minCollisionDistance * minCollisionDistance) {
		return true;
	}
	return false;
}

}
