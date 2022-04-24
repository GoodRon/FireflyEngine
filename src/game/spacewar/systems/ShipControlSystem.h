/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_SYSTEMS_PLAYER_CONTROL_H
#define SW_SYSTEMS_PLAYER_CONTROL_H

#include <firefly/systems/ISystem.h>

namespace firefly {
	class Entity;
	class ShipControls;
	class NativeEvent;
}

namespace spacewar {

class ShipControlSystem final: public firefly::ISystem {
public:
	inline static const std::string Name = "ShipControlSystem";
	
	ShipControlSystem(firefly::Engine* engine);
	~ShipControlSystem() override;

	ShipControlSystem(const ShipControlSystem&) = delete;
	ShipControlSystem& operator=(const ShipControlSystem&) = delete;

	bool onEvent(
		const std::shared_ptr<firefly::IEvent>& event) override;

private:
	void onUpdate() override;

	bool onPlayerInput(firefly::Entity* entity,
		firefly::NativeEvent* event) const;

	void onUpPressed(firefly::Entity* entity, 
		firefly::ShipControls* controls, bool isPressed) const;
	void onDownPressed(firefly::Entity* entity, 
		firefly::ShipControls* controls, bool isPressed) const;
	void onLeftPressed(firefly::Entity* entity, 
		firefly::ShipControls* controls, bool isPressed) const;
	void onRightPressed(firefly::Entity* entity, 
		firefly::ShipControls* controls, bool isPressed) const;

	void addAcceleration(firefly::Entity* entity, 
		double acceleration, double direction) const;
	
	void rotate(firefly::Entity* entity, double angle) const;
	void shoot(firefly::Entity* entity) const;
	void hyperspace(firefly::Entity* entity) const;
};

}

#endif // SW_SYSTEMS_PLAYER_CONTROL_H
