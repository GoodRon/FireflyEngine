#include "VelocitySystem.h"

#include <firefly/Entity.h>
#include <firefly/components/Velocity.h>

#include <firefly/events/SetSpeedEvent.h>
#include <firefly/events/AddSpeedEvent.h>
#include <firefly/events/SetAccelerationEvent.h>
#include <firefly/events/AddAccelerationEvent.h>

#include "misc/VelocityHelpers.h"

namespace spacewar {

constexpr double epsilon = 0.00001;

VelocitySystem::VelocitySystem(firefly::Engine* engine):
	ISystem(VelocitySystem::Name, engine) {

	addRequiredComponent(firefly::Velocity::ComponentName);
}

VelocitySystem::~VelocitySystem() {
}

bool VelocitySystem::onEvent(
	const std::shared_ptr<firefly::IEvent>& event) {

	switch (event->getType()) {
	case firefly::EventType::SetSpeed: {
		const auto speedEvent = 
			static_cast<firefly::SetSpeedEvent*>(event.get());
		if (!speedEvent) {
			return false;
		}

		setSpeed(speedEvent->getId(),
			speedEvent->getSpeed(),
			speedEvent->getDirection());
		return true;
	} break;

	case firefly::EventType::AddSpeed: {
		const auto speedEvent = 
			static_cast<firefly::AddSpeedEvent*>(event.get());
		if (!speedEvent) {
			return false;
		}

		addSpeed(speedEvent->getId(),
			speedEvent->getSpeed(),
			speedEvent->getDirection());
		return true;
	} break;

	case firefly::EventType::SetAcceleration: {
		const auto accelerationEvent = 
			static_cast<firefly::SetAccelerationEvent*>(event.get());
		if (!accelerationEvent) {
			return false;
		}

		setAcceleration(accelerationEvent->getId(),
			accelerationEvent->getAcceleration(),
			accelerationEvent->getDirection(),
			accelerationEvent->isConstant());
		return true;
	} break;

	case firefly::EventType::AddAcceleration: {
		const auto accelerationEvent = 
			static_cast<firefly::AddAccelerationEvent*>(event.get());
		if (!accelerationEvent) {
			return false;
		}

		addAcceleration(accelerationEvent->getId(),
			accelerationEvent->getAcceleration(),
			accelerationEvent->getDirection());
		return true;
	} break;

	default:
		break;
	}

	return false;
}

void VelocitySystem::onUpdate() {
	firefly::Velocity* velocity = nullptr;

	for (auto& entity: getEntities()) {
		if (!entity.second->isActive()) {
			continue;
		}

		velocity = entity.second->getComponent<firefly::Velocity>();
		processAcceleration(velocity, getElapsedMs());
	}
}

void VelocitySystem::setSpeed(firefly::EntityID id, 
	double speed, double direction) const {

	const auto entity = getEntity(id);
	if (!entity) {
		return;
	}

	const auto velocity = entity->getComponent<firefly::Velocity>();
	if (!velocity) {
		return;
	}

	velocity->speed = speed;
	velocity->speedDirection = direction;
	velocity->speedX = 0.0;
	velocity->speedY = 0.0;

	projectVector(velocity->speed, velocity->speedDirection,
		velocity->speedX, velocity->speedY);

	limitMagnitude(velocity->speed, velocity->speedDirection,
		velocity->speedX, velocity->speedY, velocity->maxSpeed);
}

void VelocitySystem::addSpeed(firefly::EntityID id, 
	double speed, double direction) const {

	const auto entity = getEntity(id);
	if (!entity) {
		return;
	}

	const auto velocity = entity->getComponent<firefly::Velocity>();
	if (!velocity) {
		return;
	}

	if (fabs(speed) < epsilon) {
		return;
	}

	projectVector(velocity->speed, velocity->speedDirection,
		velocity->speedX, velocity->speedY);

	addVector(velocity->speed, velocity->speedDirection,
		velocity->speedX, velocity->speedY,
		speed, direction);

	limitMagnitude(velocity->speed, velocity->speedDirection,
		velocity->speedX, velocity->speedY, velocity->maxSpeed);
}

void VelocitySystem::setAcceleration(firefly::EntityID id, 
	double acceleration, double direction, bool isConstant) const {

	const auto entity = getEntity(id);
	if (!entity) {
		return;
	}

	const auto velocity = entity->getComponent<firefly::Velocity>();
	if (!velocity) {
		return;
	}

	velocity->acceleration = acceleration;
	velocity->accelerationDirection = direction;
	velocity->isConstantAcceleration = isConstant;
}

void VelocitySystem::addAcceleration(firefly::EntityID id, 
	double acceleration, double direction) const {

	const auto entity = getEntity(id);
	if (!entity) {
		return;
	}

	const auto velocity = entity->getComponent<firefly::Velocity>();
	if (!velocity) {
		return;
	}

	if (fabs(acceleration) < epsilon) {
		return;
	}

	double accelerationX = 0.0;
	double accelerationY = 0.0;

	projectVector(velocity->acceleration, 
		velocity->accelerationDirection,
		accelerationX, accelerationY);

	addVector(velocity->acceleration, 
		velocity->accelerationDirection,
		accelerationX, accelerationY,
		acceleration, direction);
}

void VelocitySystem::processAcceleration(
	firefly::Velocity* velocity, 
	uint64_t elapsedMs) const {

	if (!velocity) {
		return;
	}

	if (!velocity->isActive) {
		return;
	}

	if (fabs(velocity->acceleration) < epsilon || elapsedMs == 0) {
		return;
	}

	projectVector(velocity->speed, velocity->speedDirection,
		velocity->speedX, velocity->speedY);

	addVector(velocity->speed, velocity->speedDirection,
		velocity->speedX, velocity->speedY,
		velocity->acceleration * elapsedMs / 1000.0, 
		velocity->accelerationDirection);

	limitMagnitude(velocity->speed, velocity->speedDirection,
		velocity->speedX, velocity->speedY, velocity->maxSpeed);

	if (!velocity->isConstantAcceleration) {
		velocity->acceleration = 0.0;
		velocity->accelerationDirection = 0.0;
	}
}

}
