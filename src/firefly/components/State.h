/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_COMPONENT_STATE_H
#define FIREFLY_COMPONENT_STATE_H

#include "IComponent.h"

namespace firefly {

class State final: public IComponent {
public:
	inline static const std::string ComponentName = "State";

	State() = default;
	~State() override = default;

	State(const State&) = default;
	State& operator=(const State&) = default;

	IComponent* clone() const override {
		return new State(*this);
	}
	
	int current;
	int previous;
	uint64_t timepoint = 0;
};

}

#endif // FIREFLY_COMPONENT_STATE_H
