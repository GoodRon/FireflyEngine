/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_COMPONENT_GRAVITY_H
#define FIREFLY_COMPONENT_GRAVITY_H

#include "IComponent.h"

namespace firefly {

class Gravity final: public IComponent {
public:
	inline static const std::string ComponentName = "Gravity";
	
	Gravity() = default;
	~Gravity() override = default;

	Gravity(const Gravity&) = default;
	Gravity& operator=(const Gravity&) = default;

	IComponent* clone() const override {
		return new Gravity(*this);
	}

	bool hasGravity = false;
	bool emitGravity = false;
	double mass = 0.0;
};

}

#endif // FIREFLY_COMPONENT_GRAVITY_H
