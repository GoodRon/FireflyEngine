/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_SYSTEMS_VELOCITY_H
#define SW_SYSTEMS_VELOCITY_H

#include <firefly/systems/ISystem.h>

namespace firefly {
	class Velocity;
}

namespace spacewar {

class VelocitySystem final: public firefly::ISystem {
public:
	inline static const std::string Name = "VelocitySystem";
	
	VelocitySystem(firefly::Engine* engine);
	~VelocitySystem() override;

	VelocitySystem(const VelocitySystem&) = delete;
	VelocitySystem& operator=(const VelocitySystem&) = delete;

private:
	bool onEvent(
		const std::shared_ptr<firefly::IEvent>& event) override;
	void onUpdate() override;

	void setSpeed(firefly::EntityID id, 
		double speed, double direction) const;
	void addSpeed(firefly::EntityID id, 
		double speed, double direction) const;
	void setAcceleration(firefly::EntityID id, 
		double acceleration, double direction, bool isConstant) const;
	void addAcceleration(firefly::EntityID id, 
		double acceleration, double direction) const;

	void processAcceleration(
		firefly::Velocity* velocity, 
		uint64_t elapsedMs) const;
};

}

#endif // SW_SYSTEMS_VELOCITY_H
