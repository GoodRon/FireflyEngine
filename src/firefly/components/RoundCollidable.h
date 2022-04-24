/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_COMPONENT_COLLIDABLE_H
#define FIREFLY_COMPONENT_COLLIDABLE_H

#include "IComponent.h"

namespace firefly {

class RoundCollidable final: public IComponent {
public:
	inline static const std::string ComponentName = "RoundCollidable";
	
	RoundCollidable() = default;
	~RoundCollidable() override = default;

	RoundCollidable(const RoundCollidable&) = default;
	RoundCollidable& operator=(const RoundCollidable&) = default;

	IComponent* clone() const override {
		return new RoundCollidable(*this);
	}

	bool isDestructable = false;
	double collidableRadius = 0.0;
};

}

#endif // FIREFLY_COMPONENT_COLLIDABLE_H
