/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_MAIN_STATE_H
#define SW_MAIN_STATE_H

#include <firefly/IGameState.h>

namespace firefly {
	class IEvent;
	class Engine;
	class Entity;
}

namespace spacewar {

class MainState final: public firefly::IGameState {
public:
	MainState(firefly::Engine* engine);
	~MainState() override;

	MainState(const MainState&) = delete;
	MainState& operator=(MainState&) = delete;

	void onEnter() override;
	void onExit() override;

private:
	bool onEvent(
		const std::shared_ptr<firefly::IEvent>& event) override;
	void buildObjects() override;
	void buildSystems() override;

	void configureEntity(firefly::Entity* entity) const;
};

}

#endif // SW_MAIN_STATE_H