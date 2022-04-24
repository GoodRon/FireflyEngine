/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_GAME_BUILDER_H
#define SW_GAME_BUILDER_H

#include <memory>

namespace firefly {
	class Engine;
}

namespace spacewar {

class GameBuilder {
public:
	GameBuilder(firefly::Engine* engine);
	~GameBuilder();

	GameBuilder(const GameBuilder&) = delete;
	GameBuilder& operator=(const GameBuilder&) = delete;

	bool buildGame();

private:
	class Impl;
	std::unique_ptr<Impl> _impl;
};

}

#endif // SW_GAME_BUILDER_H
