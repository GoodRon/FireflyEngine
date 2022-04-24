/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_SYSTEMS_RESPAWN_H
#define SW_SYSTEMS_RESPAWN_H

#include <firefly/systems/ISystem.h>
#include <firefly/Types.h>

namespace firefly {
	class Entity;
	class EntityManager;
}

namespace spacewar {

class RespawnSystem final: public firefly::ISystem {
public:
	inline static const std::string Name = "RespawnSystem";
	
	RespawnSystem(firefly::Engine* engine);
	~RespawnSystem() override;

	RespawnSystem(const RespawnSystem&) = delete;
	RespawnSystem& operator=(const RespawnSystem&) = delete;
	
private:
	bool onEvent(
		const std::shared_ptr<firefly::IEvent>& event) override;
	void killEntity(firefly::EntityID id) const;
	void respawnEntity(firefly::EntityID id) const;

private:
	firefly::EntityManager* _entityManager;
};

}

#endif // SW_SYSTEMS_RESPAWN_H
