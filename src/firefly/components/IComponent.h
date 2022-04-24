/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_ICOMPONENT_H
#define FIREFLY_ICOMPONENT_H

#include <string>

namespace firefly {

class IComponent {
public:
	IComponent() = default;
	virtual ~IComponent() = default;

	IComponent(const IComponent&) = default;
	IComponent& operator=(const IComponent&) = default;

	virtual IComponent* clone() const = 0;

	bool isActive = true;
};

}

#endif // FIREFLY_ICOMPONENT_H
