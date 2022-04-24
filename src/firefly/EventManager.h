/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_EVENT_MANAGER_H
#define FIREFLY_EVENT_MANAGER_H

#include <memory>
#include <queue>
#include <mutex>
#include <atomic>

namespace firefly {

class IEvent;
class SystemManager;
class StateMachine;

class EventManager {
public:
	EventManager(
		StateMachine* stateMachine);
	~EventManager();

	EventManager(const EventManager&) = delete;
	EventManager& operator=(const EventManager&) = delete;

	bool registerEvent(const std::shared_ptr<IEvent>& event);

	void processEvents();

private:
	StateMachine* const _stateMachine;
	std::atomic<bool> _hasNewEvents;
	std::mutex _queueMutex;
	std::queue<std::shared_ptr<IEvent>> _events;
};

}

#endif // FIREFLY_EVENT_MANAGER_H
 