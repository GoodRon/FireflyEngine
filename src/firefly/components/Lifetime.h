/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_COMPONENT_TEMPORAL_H
#define FIREFLY_COMPONENT_TEMPORAL_H

#include "IComponent.h"

namespace firefly {

class Lifetime final: public IComponent {
public:
	inline static const std::string ComponentName = "Lifetime";
	
	Lifetime() = default;
	~Lifetime() override = default;

	Lifetime(const Lifetime&) = default;
	Lifetime& operator=(const Lifetime&) = default;

	IComponent* clone() const override {
		return new Lifetime(*this);
	}

	uint64_t lifetimeMs = 0;
	uint64_t timepoint = 0;
};

}

#endif // FIREFLY_COMPONENT_TEMPORAL_H
