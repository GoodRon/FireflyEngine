/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_STATE_MACHINE_H
#define FIREFLY_STATE_MACHINE_H

#include <memory>
#include <unordered_map>

namespace firefly {

class IGameState;
class IEvent;

class StateMachine {
public:
	StateMachine();
	~StateMachine();

	StateMachine(const StateMachine&) = delete;
	StateMachine& operator=(const StateMachine&) = delete;

	bool pushState(std::unique_ptr<IGameState>&& state);

	bool switchState(int stateId);
	bool resetState(int stateId);

	int currentState() const;

	void clearStates();

	bool processEvent(
		const std::shared_ptr<IEvent>& event);

private:
	bool hasState(int stateId) const;

private:
	int _currentStateId;
	std::unordered_map<int, std::unique_ptr<IGameState>> _states;
};

}

#endif // FIREFLY_STATE_MACHINE_H
