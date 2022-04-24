#include "GameBuilder.h"

#include <forward_list>

#include <SDL.h>

#include <firefly/Engine.h>
#include <firefly/Entity.h>
#include <firefly/SystemManager.h>
#include <firefly/ResourceManager.h>
#include <firefly/EntityPrototypes.h>
#include <firefly/EntityManager.h>
#include <firefly/StateMachine.h>

#include "EntityBuilder.h"

#include "states/GameStates.h"
#include "states/MenuState.h"
#include "states/MainState.h"
#include "states/GameOverState.h"

namespace spacewar {

class GameBuilder::Impl {
private:
	firefly::Engine* const _engine;
	bool _isBuilt;

public:
	Impl(firefly::Engine* engine):
		_engine(engine),
		_isBuilt(false) {
	}

	~Impl() {
	}

	Impl(const Impl&) = delete;
	Impl& operator=(const Impl&) = delete;

	bool buildGame() {
		if (_isBuilt) {
			return _isBuilt;
		}

		if (!_engine) {
			return _isBuilt;
		}

		// TODO read from a config
		const std::string header("Space War!");
		const std::string icon("resources/icon.png");

		_engine->setWindowHeader(header);
		_engine->setWindowIcon(icon);

		// TODO return some error code & clean the engine

		if (!buildEntityPrototypes()) {
			return _isBuilt;
		}

		if (!buildGameStates()) {
			return _isBuilt;
		}

		_isBuilt = true;
		return _isBuilt;
	}

private:

	bool buildEntityPrototypes() const {
		const auto prototypes = _engine->getEntityPrototypes();

		// TODO read from a file
		std::forward_list<std::string> entityConfigs{
			"resources/logo.json",
			"resources/background.json", 
			"resources/player1.json", 
			"resources/player2.json", 
			"resources/star.json",
			"resources/rocket.json",
			"resources/game_over.json"
		};

		EntityBuilder builder(_engine);
		std::shared_ptr<firefly::Entity> entity;

		for (auto& config: entityConfigs) {
			entity = std::move(
				builder.buildEntity(config));

			if (!entity) {
				continue;
			}

			prototypes->registerPrototype(entity->getName(), 
				std::move(entity));
		}
		return true;
	}

	bool buildGameStates() const {

		const auto stateMachine = _engine->getStateMachine();
		std::unique_ptr<firefly::IGameState> state;

		state.reset(new MainState(_engine));
		stateMachine->pushState(std::move(state));

		state.reset(new MenuState(_engine));
		stateMachine->pushState(std::move(state));

		state.reset(new GameOverState(_engine));
		stateMachine->pushState(std::move(state));

		stateMachine->switchState(GameState::Menu);

		return true;
	}
};

GameBuilder::GameBuilder(firefly::Engine* engine):
	_impl(new Impl(engine)) {
}

GameBuilder::~GameBuilder() {
}

bool GameBuilder::buildGame() {
	return _impl->buildGame();
}

}
