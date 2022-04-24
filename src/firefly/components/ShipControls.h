/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_COMPONENT_SHIP_CONTROLS_H
#define FIREFLY_COMPONENT_SHIP_CONTROLS_H

#include <SDL_keycode.h>

#include "IComponent.h"

namespace firefly {

class ShipControls final: public IComponent {
public:
	inline static const std::string ComponentName = "ShipControls";
	
	ShipControls() = default;
	~ShipControls() override = default;

	ShipControls(const ShipControls&) = default;
	ShipControls& operator=(const ShipControls&) = default;

	IComponent* clone() const override {
		return new ShipControls(*this);
	}

	int keyCodeUp = SDLK_w;
	int keyCodeDown = SDLK_s;
	int keyCodeLeft = SDLK_a;
	int keyCodeRight = SDLK_d;

	bool isUpPressed = false;
	bool isDownPressed = false;
	bool isLeftPressed = false;
	bool isRightPressed = false;
};

}

#endif // FIREFLY_COMPONENT_SHIP_CONTROLS_H
