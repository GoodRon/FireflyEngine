/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_THE_WEDGE_WON_STATE_H
#define SW_THE_WEDGE_WON_STATE_H

#include <firefly/IGameState.h>

namespace firefly {
	class IEvent;
	class Engine;
}

namespace spacewar {

class TheWedgeWonState final : public firefly::IGameState {
public:
	TheWedgeWonState(firefly::Engine* engine);
	~TheWedgeWonState() override;

	TheWedgeWonState(const TheWedgeWonState&) = delete;
	TheWedgeWonState& operator=(TheWedgeWonState&) = delete;

	void onEnter() override;
	void onExit() override;

private:
	bool onEvent(
		const std::shared_ptr<firefly::IEvent>& event) override;

	void buildObjects() override;
};

}

#endif // SW_THE_WEDGE_WON_STATE_H
