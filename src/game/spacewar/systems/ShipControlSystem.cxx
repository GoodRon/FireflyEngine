#include "ShipControlSystem.h"

#include <SDL_timer.h>
#include <SDL_events.h>

#include <firefly/Engine.h>
#include <firefly/Entity.h>
#include <firefly/EntityPrototypes.h>
#include <firefly/EntityManager.h>
#include <firefly/EventManager.h>
#include <firefly/events/NativeEvent.h>
#include <firefly/events/StateEvent.h>
#include <firefly/events/AddAccelerationEvent.h>
#include <firefly/events/ShootEvent.h>
#include <firefly/events/PositionEvent.h>
#include <firefly/components/Player.h>
#include <firefly/components/Velocity.h>
#include <firefly/components/Position.h>
#include <firefly/components/State.h>
#include <firefly/components/Ammunition.h>
#include <firefly/components/Lifetime.h>
#include <firefly/components/ShipControls.h>
#include <firefly/components/Fuel.h>

#include "ObjectStates.h"
#include "WeaponId.h"
#include "misc/VelocityHelpers.h"

namespace spacewar {

	// TODO move to config here
	constexpr double acceleration = 3.0;
	constexpr double angleDelta = 40.0;

	ShipControlSystem::ShipControlSystem(
		firefly::Engine* engine):
		firefly::ISystem(ShipControlSystem::Name, engine) {

		addRequiredComponent(firefly::Player::ComponentName);
		addRequiredComponent(firefly::ShipControls::ComponentName);
		addRequiredComponent(firefly::Position::ComponentName);
		addRequiredComponent(firefly::Velocity::ComponentName);
		addRequiredComponent(firefly::State::ComponentName);
		addRequiredComponent(firefly::Ammunition::ComponentName);
		addRequiredComponent(firefly::Fuel::ComponentName);
	}

	ShipControlSystem::~ShipControlSystem() {
	}

	void ShipControlSystem::onUpdate() {
		for (auto& entity: getEntities()) {
			if (!entity.second->isActive()) {
				continue;
			}

			const auto controls = entity.second->
				getComponent<firefly::ShipControls>();
			if (!controls) {
				continue;
			}

			onUpPressed(entity.second, 
				controls, controls->isUpPressed);
			onDownPressed(entity.second, 
				controls, controls->isDownPressed);
			onLeftPressed(entity.second, 
				controls, controls->isLeftPressed);
			onRightPressed(entity.second, 
				controls, controls->isRightPressed);
		}
	}

	bool ShipControlSystem::onEvent(
		const std::shared_ptr<firefly::IEvent>& event) {
		if (!event) {
			return false;
		}

		if (event->getType() != firefly::EventType::Native) {
			return false;
		}

		const auto nativeEvent = 
			static_cast<firefly::NativeEvent*>(event.get());
		
		for (auto& entity: getEntities()) {
			if (!entity.second->isActive()) {
				continue;
			}

			if (onPlayerInput(entity.second, nativeEvent)) {
				return true;
			}
		}
		return false;
	}

	bool ShipControlSystem::onPlayerInput(
		firefly::Entity* entity,
		firefly::NativeEvent* event) const {

		if (!entity || !event) {
			return false;
		}

		const auto controls = entity->getComponent<firefly::ShipControls>();
		if (!controls) {
			return false;
		}
		
		auto sdlEvent = event->getSDLEvent();
		int keyCode = 0;
		switch (sdlEvent.type) {
		case SDL_KEYDOWN:
			keyCode = sdlEvent.key.keysym.sym;
			if (controls->keyCodeUp == keyCode) {
				onUpPressed(entity, controls, true);
				return true;
			}
			
			if (controls->keyCodeLeft == keyCode) {
				onLeftPressed(entity, controls, true);
				return true;
			}

			if (controls->keyCodeDown == keyCode) {
				onDownPressed(entity, controls, true);
				return true;
			}

			if (controls->keyCodeRight == keyCode) {
				onRightPressed(entity, controls, true);
				return true;
			}
			break;

		case SDL_KEYUP:
			keyCode = sdlEvent.key.keysym.sym;
			if (controls->keyCodeUp == keyCode) {
				onUpPressed(entity, controls, false);
				return true;
			}
			
			if (controls->keyCodeLeft == keyCode) {
				onLeftPressed(entity, controls, false);
				return true;
			}
			
			if (controls->keyCodeDown == keyCode) {
				onDownPressed(entity, controls, false);
				return true;
			}

			if (controls->keyCodeRight == keyCode) {
				onRightPressed(entity, controls, false);
				return true;
			}
			break;

		default:
			break;
		}
		return false;
	}

	void ShipControlSystem::onUpPressed(
		firefly::Entity* entity, 
		firefly::ShipControls* controls, 
		bool isPressed) const {

		controls->isUpPressed = isPressed;

		const auto fuelComponent = 
			entity->getComponent<firefly::Fuel>();
		
		const auto stateComponent = 
			entity->getComponent<firefly::State>();

		const auto eventManager = getEngine()->getEventManager();

		if (!controls->isUpPressed) {
			// TODO make a swichState func
			if (stateComponent->current != ObjectState::Moving) {
				return;
			}

			std::shared_ptr<firefly::IEvent> event(new firefly::StateEvent(
				entity->getId(), ObjectState::Idle));
						
			eventManager->registerEvent(std::move(event));
			return;
		} 

		constexpr double epsilon = 0.000001;
		if (fuelComponent->max > 0.0 && fuelComponent->current < epsilon) {
			return;
		}

		const auto positionComponent = 
			entity->getComponent<firefly::Position>();

		addAcceleration(
			entity, acceleration, positionComponent->direction);

		if (stateComponent->current != ObjectState::Idle) {
			return;
		}

		std::shared_ptr<firefly::IEvent> event(new firefly::StateEvent(
				entity->getId(), ObjectState::Moving));
						
		eventManager->registerEvent(std::move(event));
	}

	void ShipControlSystem::onDownPressed(
		firefly::Entity* entity, 
		firefly::ShipControls* controls, 
		bool isPressed) const {

		controls->isDownPressed = isPressed;

		if (!controls->isDownPressed) {
			return;
		}

		const auto stateComponent =
			entity->getComponent<firefly::State>();

		if (stateComponent->current != ObjectState::Idle &&
			stateComponent->current != ObjectState::Moving) {
			return;
		}

		shoot(entity);
	}

	void ShipControlSystem::onLeftPressed(
		firefly::Entity* entity, 
		firefly::ShipControls* controls, 
		bool isPressed) const {

		controls->isLeftPressed = isPressed;

		if (controls->isLeftPressed && controls->isRightPressed) {
			hyperspace(entity);
			return;
		}

		if (controls->isLeftPressed) {
			rotate(entity, -angleDelta * getElapsedMs() / 1000.0);
			return;	
		}

		if (controls->isRightPressed) {
			onRightPressed(entity, controls, controls->isRightPressed);
			return;
		}
	}

	void ShipControlSystem::onRightPressed(
		firefly::Entity* entity, 
		firefly::ShipControls* controls, 
		bool isPressed) const {

		controls->isRightPressed = isPressed;

		if (controls->isLeftPressed && controls->isRightPressed) {
			hyperspace(entity);
			return;
		}

		if (controls->isRightPressed) {
			rotate(entity, angleDelta * getElapsedMs() / 1000.0);
			return;	
		}

		if (controls->isLeftPressed) {
			onLeftPressed(entity, controls, controls->isLeftPressed);
			return;
		}
	}

	void ShipControlSystem::addAcceleration(
		firefly::Entity* entity,
		double acceleration, double direction) const {

		std::shared_ptr<firefly::IEvent> event(
			new firefly::AddAccelerationEvent(
				entity->getId(), acceleration, direction));
		
		const auto eventManager = getEngine()->getEventManager();			
		eventManager->registerEvent(std::move(event));
	}

	void ShipControlSystem::rotate(
		firefly::Entity* entity, 
		double angle) const {

		const auto stateComponent = 
			entity->getComponent<firefly::State>();
		if (stateComponent->current != ObjectState::Idle &&
			stateComponent->current != ObjectState::Moving) {
			return;
		}

		const auto positionComponent = 
			entity->getComponent<firefly::Position>();

		std::shared_ptr<firefly::IEvent> event(
			new firefly::PositionEvent(
				entity->getId(), positionComponent->x, positionComponent->y,
				normalizeAngle(positionComponent->direction + angle)));

		const auto eventManager = getEngine()->getEventManager();
		eventManager->registerEvent(std::move(event));
	}

	void ShipControlSystem::shoot(firefly::Entity* entity) const {
		const auto stateComponent = 
			entity->getComponent<firefly::State>();

		if (stateComponent->current != ObjectState::Idle &&
			stateComponent->current != ObjectState::Moving) {
			return;
		}

		std::shared_ptr<firefly::IEvent> event(
			new firefly::ShootEvent(
				entity->getId(), WeaponId::RocketLauncher));

		const auto eventManager = getEngine()->getEventManager();
		eventManager->registerEvent(std::move(event));
	}

	void ShipControlSystem::hyperspace(firefly::Entity* entity) const {

		const auto stateComponent = 
			entity->getComponent<firefly::State>();

		if (stateComponent->current != ObjectState::Idle &&
			stateComponent->current != ObjectState::Moving) {
			return;
		}

		std::shared_ptr<firefly::IEvent> event(new firefly::StateEvent(
			entity->getId(), ObjectState::Hyperspace));
					
		const auto eventManager = getEngine()->getEventManager();
		eventManager->registerEvent(std::move(event));
	}
}
