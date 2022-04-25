/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_COMPONENT_HYPERSPACE_H
#define FIREFLY_COMPONENT_HYPERSPACE_H

#include "IComponent.h"

namespace firefly {

class Hyperspace final: public IComponent {
public:
	inline static const std::string ComponentName = "Hyperspace";
	
	Hyperspace() = default;
	~Hyperspace() override = default;

	Hyperspace(const Hyperspace&) = default;
	Hyperspace& operator=(const Hyperspace&) = default;

	IComponent* clone() const override {
		return new Hyperspace(*this);
	}

	uint64_t hyperspaceTimeMs = 0;
	uint64_t cooldownMs = 0;
	uint64_t chanceOfMulfunction = 0;
	uint64_t timepoint = 0;
};

}

#endif // FIREFLY_COMPONENT_HYPERSPACE_H
