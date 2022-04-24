/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_SYSTEMS_POSITIONING_H
#define SW_SYSTEMS_POSITIONING_H

#include <firefly/systems/ISystem.h>

namespace firefly {
	class Position;
	class Velocity;
}

namespace spacewar {

class PositioningSystem final: public firefly::ISystem {
public:
	inline static const std::string Name = "PositioningSystem";
	
	PositioningSystem(firefly::Engine* engine);
	~PositioningSystem() override;

	PositioningSystem(const PositioningSystem&) = delete;
	PositioningSystem& operator=(const PositioningSystem&) = delete;

private:
	bool onEvent(
		const std::shared_ptr<firefly::IEvent>& event) override;
	void onUpdate() override;
	
	void updatePosition(firefly::EntityID id, 
		double x, double y, double direction) const;

	void processPosition(
		firefly::Position* position, 
		firefly::Velocity* velocity) const;

	void wrapCoordinates(
		firefly::Position* position) const;
};

}

#endif // SW_SYSTEMS_POSITIONING_H
