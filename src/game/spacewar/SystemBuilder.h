/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_SYSTEM_BUILDER_H
#define SW_SYSTEM_BUILDER_H

#include <memory>
#include <string>

namespace firefly {
	class Engine;
	class ISystem;
}

namespace spacewar {

std::shared_ptr<firefly::ISystem> buidSystem(
	const std::string& name,
	firefly::Engine* engine);

}

#endif // SW_SYSTEM_BUILDER_H
