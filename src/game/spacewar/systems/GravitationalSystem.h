/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_SYSTEMS_GRAVITATION_H
#define SW_SYSTEMS_GRAVITATION_H

#include <unordered_map>

#include <firefly/systems/ISystem.h>
#include <firefly/Types.h>

namespace firefly {
	class Entity;
}

namespace spacewar {

class GravitationalSystem final: public firefly::ISystem {
public:
	inline static const std::string Name = "GravitationalSystem";

	GravitationalSystem(firefly::Engine* engine);
	~GravitationalSystem() override;

	GravitationalSystem(const GravitationalSystem&) = delete;
	GravitationalSystem& operator=(const GravitationalSystem&) = delete;

private:
	void onUpdate() override;
	bool onRegisterEntity(firefly::Entity* entity) override;
	void onUnregisterEntity(firefly::Entity* entity) override;

	void processGravity(
		firefly::Entity* gravityEmitter) const;

private:
	std::unordered_map<firefly::EntityID, firefly::Entity*> _gravityEmitters;
};

}

#endif // SW_SYSTEMS_GRAVITATION_H
