/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_ENGINE_EXCEPTION_H
#define FIREFLY_ENGINE_EXCEPTION_H

#include <stdexcept>
#include <string>

namespace firefly {

class EngineException: public std::runtime_error {
public:
	EngineException(const std::string& what) : std::runtime_error(what) {}
};

}

#endif // FIREFLY_ENGINE_EXCEPTION_H
