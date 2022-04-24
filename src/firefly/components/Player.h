/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_COMPONENT_PLAYER_H
#define FIREFLY_COMPONENT_PLAYER_H

#include "IComponent.h"

namespace firefly {

class Player final: public IComponent {
public:
	inline static const std::string ComponentName = "Player";
	
	Player() = default;
	~Player() override = default;

	Player(const Player&) = default;
	Player& operator=(const Player&) = default;

	IComponent* clone() const override {
		return new Player(*this);
	}

	int playerId = 0;
	std::string playerName;
};

}

#endif // FIREFLY_COMPONENT_PLAYER_H
