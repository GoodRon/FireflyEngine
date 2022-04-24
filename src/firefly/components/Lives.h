/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_COMPONENT_LIVES_H
#define FIREFLY_COMPONENT_LIVES_H

#include "IComponent.h"

namespace firefly {

class Lives final: public IComponent {
public:
	inline static const std::string ComponentName = "Lives";
	
	Lives() = default;
	~Lives() override = default;

	Lives(const Lives&) = default;
	Lives& operator=(const Lives&) = default;

	IComponent* clone() const override {
		return new Lives(*this);
	}

	int maxLives = 0;
	int currentLives = 0;
};

}

#endif // FIREFLY_COMPONENT_LIVES_H
