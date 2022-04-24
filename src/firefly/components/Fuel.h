/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_COMPONENT_FUEL_H
#define FIREFLY_COMPONENT_FUEL_H

#include "IComponent.h"

namespace firefly {

class Fuel final: public IComponent {
public:
	inline static const std::string ComponentName = "Fuel";
	
	Fuel() = default;
	~Fuel() override = default;

	Fuel(const Fuel&) = default;
	Fuel& operator=(const Fuel&) = default;

	IComponent* clone() const override {
		return new Fuel(*this);
	}

	double max = 0.0;
	double current = 0.0;
	double consumption = 0.0;
};

}

#endif // FIREFLY_COMPONENT_FUEL_H
