/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_SYSTEMS_LIFETIME_H
#define SW_SYSTEMS_LIFETIME_H

#include <firefly/systems/ISystem.h>
#include <firefly/Types.h>

namespace firefly {
	class Entity;
}

namespace spacewar {

class LifetimeSystem final: public firefly::ISystem {
public:
	inline static const std::string Name = "LifetimeSystem";

	LifetimeSystem(firefly::Engine* engine);
	~LifetimeSystem() override;

	LifetimeSystem(const LifetimeSystem&) = delete;
	LifetimeSystem& operator=(const LifetimeSystem&) = delete;
	
private:
	void onUpdate() override;
	bool isEntityExpired(firefly::Entity* entity) const;
};

}

#endif // SW_SYSTEMS_LIFETIME_H
