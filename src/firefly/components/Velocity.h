/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_COMPONENT_VELOCITY_H
#define FIREFLY_COMPONENT_VELOCITY_H

#include "IComponent.h"

namespace firefly {

class Velocity final: public IComponent {
public:
	inline static const std::string ComponentName = "Velocity";
	
	Velocity() = default;
	~Velocity() override = default;

	Velocity(const Velocity&) = default;
	Velocity& operator=(const Velocity&) = default;

	IComponent* clone() const override {
		return new Velocity(*this);
	}

	double speed = 0.0;
	double speedDirection = 0.0;
	double maxSpeed = 0.0;
	double acceleration = 0.0;
	double accelerationDirection = 0.0;
	bool isConstantAcceleration = false;
	double rotation = 0.0;

	double speedX = 0.0;
	double speedY = 0.0;
};

}

#endif // FIREFLY_COMPONENT_VELOCITY_H
