#include "EntityBuilder.h"

#include <functional>
#include <unordered_map>
#include <fstream>

#include <firefly/Engine.h>
#include <firefly/ResourceManager.h>
#include <firefly/Entity.h>
#include <firefly/Frame.h>

#include <firefly/components/Visual.h>
#include <firefly/components/Position.h>
#include <firefly/components/Velocity.h>
#include <firefly/components/Player.h>
#include <firefly/components/Gravity.h>
#include <firefly/components/State.h>
#include <firefly/components/Ammunition.h>
#include <firefly/components/Lifetime.h>
#include <firefly/components/Lives.h>
#include <firefly/components/RoundCollidable.h>
#include <firefly/components/ShipControls.h>
#include <firefly/components/Fuel.h>

#include "rapidjson/document.h"

namespace spacewar {

class EntityBuilder::Impl {
private:
	using componentBuilder = std::function<bool(
		firefly::Entity* entity,
		rapidjson::Value& document)>;

	firefly::Engine* const _engine;
	std::unordered_map<std::string, componentBuilder> _componentBuilders;

public:

	Impl(firefly::Engine* engine):
		_engine(engine),
		_componentBuilders() {

		registerComponentBuilders();
	}

	~Impl() {
	}

	Impl(const Impl&) = delete;
	Impl& operator=(const Impl&) = delete;

	std::shared_ptr<firefly::Entity> buildEntity(
		const std::string& jsonConfig) {
		if (!_engine) {
			return nullptr;
		}

		std::ifstream jsonFile;
		jsonFile.open(jsonConfig);
		if (!jsonFile.good()) {
			return nullptr;
		}

		std::string line;
		std::string jsonContent;
		while (getline(jsonFile, line)) {
			jsonContent += line;
		}

		rapidjson::Document document;
		document.Parse(jsonContent.c_str());

		if (document.HasParseError()) {
			// TODO log error
			return false;
		}

		auto entityName = std::string(document["name"].GetString());

		std::shared_ptr<firefly::Entity> entity(new firefly::Entity(entityName));

		for (auto& component: document["components"].GetArray()) {
			const auto componentName = std::string(component["name"].GetString());

			if (_componentBuilders.find(componentName) == _componentBuilders.end()) {
				// TODO notify about error
				continue;
			}

			// TODO check result
			_componentBuilders[componentName](entity.get(), component);
		}

		return entity;
	}

private:
	void registerComponentBuilders() {
		_componentBuilders[firefly::Visual::ComponentName] = [this](
			firefly::Entity* entity,
			rapidjson::Value& document)->bool {
			return buildVisualComponent(entity, document);
		};

		_componentBuilders[firefly::Position::ComponentName] = [this](
			firefly::Entity* entity,
			rapidjson::Value& document)->bool {
			return buildPositionComponent(entity, document);
		};

		_componentBuilders[firefly::Velocity::ComponentName] = [this](
			firefly::Entity* entity,
			rapidjson::Value& document)->bool {
			return buildVelocityComponent(entity, document);
		};

		_componentBuilders[firefly::Player::ComponentName] = [this](
			firefly::Entity* entity,
			rapidjson::Value& document)->bool {
			return buildPlayerComponent(entity, document);
		};
		_componentBuilders[firefly::Gravity::ComponentName] = [this](
			firefly::Entity* entity,
			rapidjson::Value& document)->bool {
			return buildGravityComponent(entity, document);
		};

		_componentBuilders[firefly::State::ComponentName] = [this](
			firefly::Entity* entity,
			rapidjson::Value& document)->bool {
			return buildStateComponent(entity, document);
		};

		_componentBuilders[firefly::Ammunition::ComponentName] = [this](
			firefly::Entity* entity,
			rapidjson::Value& document)->bool {
			return buildAmmunitionComponent(entity, document);
		};

		_componentBuilders[firefly::Lifetime::ComponentName] = [this](
			firefly::Entity* entity,
			rapidjson::Value& document)->bool {
			return buildLifetimeComponent(entity, document);
		};

		_componentBuilders[firefly::RoundCollidable::ComponentName] = [this](
			firefly::Entity* entity,
			rapidjson::Value& document)->bool {
			return buildRoundCollidableComponent(entity, document);
		};

		_componentBuilders[firefly::Lives::ComponentName] = [this](
			firefly::Entity* entity,
			rapidjson::Value& document)->bool {
			return buildLivesComponent(entity, document);
		};

		_componentBuilders[firefly::ShipControls::ComponentName] = [this](
			firefly::Entity* entity,
			rapidjson::Value& document)->bool {
			return buildShipControlsComponent(entity, document);
		};

		_componentBuilders[firefly::Fuel::ComponentName] = [this](
			firefly::Entity* entity,
			rapidjson::Value& document)->bool {
			return buildFuelComponent(entity, document);
		};
	}

	bool buildVisualComponent(
		firefly::Entity* entity,
		rapidjson::Value& document) const {

		if (!entity) {
			return false;
		}

		auto resourceManager = _engine->getResourceManager();
		if (!resourceManager) {
			return false;
		}

		std::unique_ptr<firefly::Visual> component(new firefly::Visual);
		component->zIndex = document["zIndex"].GetInt();
		component->isVisible = document["isVisible"].GetBool();
		component->currentState = document["currentState"].GetInt();

		for (auto& state: document["states"].GetArray()) {
			const auto stateValue = state["state"].GetInt();
			const auto texturePath = std::string(state["texture"].GetString());

			const auto texture = resourceManager->loadTexture(texturePath);
			if (!texture) {
				// TODO log error
				return false;
			}

			SDL_Rect frameRect;
			frameRect.w = state["frameWidth"].GetInt();
			frameRect.h = state["frameHeight"].GetInt();
			const uint64_t duration = state["frameDuration"].GetUint64();

			firefly::Visual::State visualState;
			visualState.isLooped = state["isLooped"].GetBool();

			const int row = state["frameRow"].GetInt();
			const int col = state["frameCol"].GetInt();
			const int amount = state["frameAmount"].GetInt();

			std::vector<std::shared_ptr<firefly::Frame>> frames;

			frameRect.y = row * frameRect.h;
			for (int frameCount = 0; frameCount < amount; ++frameCount) {
				frameRect.x = (col + frameCount) * frameRect.w;
					
				frames.emplace_back(
					new firefly::Frame(texture, frameRect, duration));
			}

			visualState.frames = std::move(frames);

			component->states[stateValue] = std::move(visualState);
		}

		entity->addComponent(firefly::Visual::ComponentName, std::move(component));
		return true;
	}

	bool buildPositionComponent(
		firefly::Entity* entity,
		rapidjson::Value& document) const {

		std::unique_ptr<firefly::Position> component(new firefly::Position);

		component->x = document["x"].GetDouble();
		component->y = document["y"].GetDouble();
		component->centerX = document["centerX"].GetDouble();
		component->centerY = document["centerY"].GetDouble();
		component->width = document["width"].GetDouble();
		component->height = document["height"].GetDouble();
		component->scale = document["scale"].GetDouble();
		component->direction = document["direction"].GetDouble();

		entity->addComponent(firefly::Position::ComponentName, std::move(component));
		return true;
	}

	bool buildVelocityComponent(
		firefly::Entity* entity,
		rapidjson::Value& document) const {

		std::unique_ptr<firefly::Velocity> component(new firefly::Velocity);

		component->speed = document["speed"].GetDouble();
		component->speedDirection = document["speedDirection"].GetDouble();
		component->maxSpeed = document["maxSpeed"].GetDouble();
		component->acceleration = document["acceleration"].GetDouble();
		component->accelerationDirection = document["accelerationDirection"].GetDouble();
		component->isConstantAcceleration = document["isConstantAcceleration"].GetBool();

		entity->addComponent(firefly::Velocity::ComponentName, std::move(component));
		return true;
	}

	bool buildPlayerComponent(
		firefly::Entity* entity,
		rapidjson::Value& document) const {

		std::unique_ptr<firefly::Player> component(new firefly::Player);

		component->playerId = document["playerId"].GetInt();
		component->playerName = std::string(document["playerName"].GetString());

		entity->addComponent(firefly::Player::ComponentName, std::move(component));
		return true;
	}

	bool buildGravityComponent(
		firefly::Entity* entity,
		rapidjson::Value& document) const {

		std::unique_ptr<firefly::Gravity> component(new firefly::Gravity);

		component->hasGravity = document["hasGravity"].GetBool();
		component->emitGravity = document["emitGravity"].GetBool();
		component->mass = document["mass"].GetDouble();

		entity->addComponent(firefly::Gravity::ComponentName, std::move(component));
		return true;
	}

	bool buildStateComponent(
		firefly::Entity* entity,
		rapidjson::Value& document) const {

		std::unique_ptr<firefly::State> component(new firefly::State);

		component->current = document["current"].GetInt();
		component->previous = document["previous"].GetInt();

		entity->addComponent(firefly::State::ComponentName, std::move(component));
		return true;
	}

	bool buildAmmunitionComponent(
		firefly::Entity* entity,
		rapidjson::Value& document) const {

		std::unique_ptr<firefly::Ammunition> component(new firefly::Ammunition);

		for (auto& weaponData: document["weapons"].GetArray()) {
			firefly::Ammunition::Weapon weapon;

			const int weaponId = weaponData["weaponId"].GetInt();
			weapon.projectile = std::string(weaponData["projectile"].GetString());
			weapon.maxRounds = weaponData["maxRounds"].GetInt();
			weapon.rounds = weapon.maxRounds;
			weapon.cooldownTimeMs = weaponData["cooldownTimeMs"].GetUint64();

			component->weapons[weaponId] = std::move(weapon);
		}
		
		entity->addComponent(firefly::Ammunition::ComponentName, std::move(component));
		return true;
	}

	bool buildLifetimeComponent(
		firefly::Entity* entity,
		rapidjson::Value& document) const {

		std::unique_ptr<firefly::Lifetime> component(new firefly::Lifetime);

		component->lifetimeMs = document["lifetimeMs"].GetUint64();

		entity->addComponent(firefly::Lifetime::ComponentName, std::move(component));
		return true;
	}

	bool buildRoundCollidableComponent(
		firefly::Entity* entity,
		rapidjson::Value& document) const {

		std::unique_ptr<firefly::RoundCollidable> component(
			new firefly::RoundCollidable);

		component->isDestructable = document["isDestructable"].GetBool();
		component->collidableRadius = document["collidableRadius"].GetDouble();

		entity->addComponent(firefly::RoundCollidable::ComponentName, 
			std::move(component));
		return true;
	}

	bool buildLivesComponent(
		firefly::Entity* entity,
		rapidjson::Value& document) const {

		std::unique_ptr<firefly::Lives> component(
			new firefly::Lives);

		component->maxLives = document["maxLives"].GetInt();
		component->currentLives = component->maxLives;

		entity->addComponent(firefly::Lives::ComponentName, 
			std::move(component));
		return true;
	}

	bool buildShipControlsComponent(
		firefly::Entity* entity,
		rapidjson::Value& document) const {

		std::unique_ptr<firefly::ShipControls> component(
			new firefly::ShipControls);

		entity->addComponent(firefly::ShipControls::ComponentName, 
			std::move(component));
		return true;
	}

	bool buildFuelComponent(
		firefly::Entity* entity,
		rapidjson::Value& document) const {

		std::unique_ptr<firefly::Fuel> component(
			new firefly::Fuel);

		component->max = document["max"].GetDouble();
		component->current = document["current"].GetDouble();
		component->consumption = document["consumption"].GetDouble();

		entity->addComponent(firefly::Fuel::ComponentName, 
			std::move(component));
		return true;
	}
};

EntityBuilder::EntityBuilder(firefly::Engine* engine):
	_impl(new Impl(engine)) {
}

EntityBuilder::~EntityBuilder() {
}

std::shared_ptr<firefly::Entity> 
EntityBuilder::buildEntity(const std::string& jsonConfig) {
	return _impl->buildEntity(jsonConfig);
}

}

