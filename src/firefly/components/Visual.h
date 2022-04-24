/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_COMPONENT_VISUAL_H
#define FIREFLY_COMPONENT_VISUAL_H

#include <unordered_map>
#include <vector>

#include "IComponent.h"

namespace firefly {

class Frame;

class Visual final: public IComponent {
public:
	inline static const std::string ComponentName = "Visual";

	Visual() = default;
	~Visual() override = default;

	Visual(const Visual&) = default;
	Visual& operator=(const Visual&) = default;

	IComponent* clone() const override {
		return new Visual(*this);
	}
	
	bool hasState(int state) {
		if (states.find(state) == states.end()) {
			return false;
		}
		return true;
	}

	struct State {
		std::vector<std::shared_ptr<Frame>> frames;
		bool isLooped = true;
		bool isFinished = false;
	};

	int currentState = 0;
	size_t frameIndex = 0; 
	std::unordered_map<int, State> states;
	bool isPaused = false;
	bool isVisible = false;
	int zIndex = 0;
	uint64_t timepoint = 0;
};

}

#endif // FIREFLY_COMPONENT_VISUAL_H
