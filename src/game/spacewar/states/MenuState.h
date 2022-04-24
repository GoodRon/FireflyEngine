/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_MENU_STATE_H
#define SW_MENU_STATE_H

#include <firefly/IGameState.h>

namespace firefly {
	class IEvent;
	class Engine;
}

namespace spacewar {

class MenuState final : public firefly::IGameState {
public:
	MenuState(firefly::Engine* engine);
	~MenuState() override;

	MenuState(const MenuState&) = delete;
	MenuState& operator=(MenuState&) = delete;

	void onEnter() override;
	void onExit() override;

private:
	bool onEvent(
		const std::shared_ptr<firefly::IEvent>& event) override;

	void buildObjects() override;
};

}

#endif // SW_MENU_STATE_H
