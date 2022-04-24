/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_COMPONENT_AMMUNITION_H
#define FIREFLY_COMPONENT_AMMUNITION_H

#include <unordered_map>

#include "IComponent.h"

namespace firefly {

class Ammunition final: public IComponent {
public:
	inline static const std::string ComponentName = "Ammunition";
	
	Ammunition() = default;
	~Ammunition() override = default;

	Ammunition(const Ammunition&) = default;
	Ammunition& operator=(const Ammunition&) = default;

	IComponent* clone() const override {
		return new Ammunition(*this);
	}

	struct Weapon {
		std::string projectile;
		int rounds = 0;
		int maxRounds = 0;
		uint64_t cooldownTimeMs = 0;
		uint64_t lastShotTimepoint = 0;
	};

	std::unordered_map<int, Weapon> weapons;
};

}

#endif // FIREFLY_COMPONENT_AMMUNITION_H
