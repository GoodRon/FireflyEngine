/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_GAME_OVER_STATE_H
#define SW_GAME_OVER_STATE_H

#include <firefly/IGameState.h>

namespace firefly {
	class IEvent;
	class Engine;
}

namespace spacewar {

class GameOverState final : public firefly::IGameState {
public:
	GameOverState(firefly::Engine* engine);
	~GameOverState() override;

	GameOverState(const GameOverState&) = delete;
	GameOverState& operator=(GameOverState&) = delete;

	void onEnter() override;
	void onExit() override;

private:
	bool onEvent(
		const std::shared_ptr<firefly::IEvent>& event) override;

	void buildObjects() override;
};

}

#endif // SW_GAME_OVER_STATE_H
