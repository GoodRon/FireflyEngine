/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <SDL_log.h>

#include <firefly/Engine.h>
#include <firefly/EngineException.h>

#include "GameBuilder.h"

int main(int, char**) {
	// TODO read from a config
	const int width = 1500;
	const int height = 1000;

	int ret = -1;
	try {

		firefly::Engine engine(width, height);
		spacewar::GameBuilder gameBuilder(&engine);
		
		if (!gameBuilder.buildGame()) {
			return ret;
		}

		ret = engine.run();

	} catch (firefly::EngineException& exception) {
		SDL_Log("Engine exception caught: %s", exception.what());
	}
	return ret;
}
