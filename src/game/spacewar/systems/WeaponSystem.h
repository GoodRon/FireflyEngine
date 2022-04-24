/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_SYSTEMS_WEAPON_H
#define SW_SYSTEMS_WEAPON_H

#include <firefly/systems/ISystem.h>

namespace firefly {
	class Entity;
	class IEvent;
}

namespace spacewar {

class WeaponSystem final: public firefly::ISystem {
public:
	inline static const std::string Name = "WeaponSystem";

	WeaponSystem(firefly::Engine* engine);
	~WeaponSystem() override;

	WeaponSystem(const WeaponSystem&) = delete;
	WeaponSystem& operator=(const WeaponSystem&) = delete;
	
private:
	bool onEvent(
		const std::shared_ptr<firefly::IEvent>& event);
	
	void shoot(firefly::Entity* entity, int weaponId) const;
	void reload(firefly::Entity* entity, 
		int weaponId, int rounds) const;
};

}

#endif // SW_SYSTEMS_WEAPON_H
