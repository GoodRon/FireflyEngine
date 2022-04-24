/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_COMPONENT_POSITION_H
#define FIREFLY_COMPONENT_POSITION_H

#include <SDL_rect.h>

#include "IComponent.h"

namespace firefly {

class Position final: public IComponent {
public:
	inline static const std::string ComponentName = "Position";
	
	Position() = default;
	~Position() override = default;

	Position(const Position&) = default;
	Position& operator=(const Position&) = default;

	IComponent* clone() const override {
		return new Position(*this);
	}

	SDL_Rect toRect() {
		auto point = center();

		return SDL_Rect{ 
			static_cast<int>(x - point.x), 
			static_cast<int>(y - point.y),
			static_cast<int>(width * scale), 
			static_cast<int>(height * scale)};
	}

	SDL_Point center() {
		return SDL_Point{
			static_cast<int>(centerX * scale),
			static_cast<int>(centerY * scale)
		};
	}

	double x = 0.0;
	double y = 0.0;
	double direction = 0.0;
	double width = 0.0;
	double height = 0.0;
	double centerX = 0.0;
	double centerY = 0.0;
	double scale = 0.0;
};

}

#endif // FIREFLY_COMPONENT_POSITION_H
