/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_SYSTEMS_COLLISION_H
#define SW_SYSTEMS_COLLISION_H

#include <memory>

#include <firefly/systems/ISystem.h>

namespace firefly {
	class RoundCollidable;
	class Position;
}

namespace spacewar {

class EntityQuadtree;

class CollisionSystem final: public firefly::ISystem {
public:
	inline static const std::string Name = "CollisionSystem";

	CollisionSystem(firefly::Engine* engine);
	~CollisionSystem() override;

	CollisionSystem(const CollisionSystem&) = delete;
	CollisionSystem& operator=(const CollisionSystem&) = delete;

private:
	void onUpdate() override;

	bool isCollided(
		firefly::RoundCollidable* collidableLeft,
		firefly::Position* positionLeft,
		firefly::RoundCollidable* collidableRight,
		firefly::Position* positionRigth) const;

private:
	std::unique_ptr<EntityQuadtree> _qauadtree;
};

}

#endif // SW_SYSTEMS_COLLISION_H
