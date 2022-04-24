/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_SYSTEMS_FUEL_H
#define SW_SYSTEMS_FUEL_H

#include <firefly/systems/ISystem.h>
#include <firefly/Types.h>

namespace firefly {
	class Fuel;
	class State;
}

namespace spacewar {

class FuelSystem final: public firefly::ISystem {
public:
	inline static const std::string Name = "FuelSystem";

	FuelSystem(firefly::Engine* engine);
	~FuelSystem() override;

	FuelSystem(const FuelSystem&) = delete;
	FuelSystem& operator=(const FuelSystem&) = delete;
	
private:
	bool onEvent(
		const std::shared_ptr<firefly::IEvent>& event);
	void onUpdate() override;

	void updateFuel(firefly::EntityID id, 
		firefly::Fuel* fuel, firefly::State* state) const;
	void setFuel(firefly::EntityID id, 
		double current, double max) const;
};

}

#endif // SW_SYSTEMS_FUEL_H
