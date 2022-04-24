/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_SYSTEM_EVENT_H
#define FIREFLY_SYSTEM_EVENT_H

#include <string>

#include "IEvent.h"

namespace firefly {

class Entity;

class SystemEvent final: public IEvent {
public:
	SystemEvent(const std::string& systemName,
		bool isRemoved = false);
	~SystemEvent() override;

	std::string getSystemName() const;
	bool isRemoved() const;

private:
	const std::string _systemName;
	const bool _isRemoved;
};

}

#endif // FIREFLY_SYSTEM_EVENT_H
