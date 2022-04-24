/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_COMPONENT_HEALTH_H
#define FIREFLY_COMPONENT_HEALTH_H

#include "IComponent.h"

namespace firefly {

class Health final: public IComponent {
public:
	inline static const std::string ComponentName = "Health";
	
	Health() = default;
	~Health() override = default;

	Health(const Health&) = default;
	Health& operator=(const Health&) = default;

	IComponent* clone() const override {
		return new Health(*this);
	}

	int max = 0;
	int current = 0;
};

}

#endif // FIREFLY_COMPONENT_HEALTH_H
