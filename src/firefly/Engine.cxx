#include <SDL_timer.h>

#include "Engine.h"
#include "Entity.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "EntityManager.h"
#include "EngineException.h"
#include "SystemManager.h"
#include "EventManager.h"
#include "EntityPrototypes.h"
#include "StateMachine.h"

#include "systems/RenderingSystem.h"
#include "events/NativeEvent.h"
#include "events/UpdateEvent.h"
#include "components/IComponent.h"

namespace firefly {

constexpr size_t maxQueuedEvents = 1024;

Engine::Engine(int width, int height):
	_isRunning(true),
	_returnCode(0),
	_renderer(),
	_resourceManager(),
	_entityManager(),
	_entityPrototypes(),
	_systemManager(),
	_eventManager(),
	_renderingSystem(),
	_stateMachine() {

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		throw EngineException(SDL_GetError());
	}

	_stateMachine.reset(new StateMachine);

	_eventManager.reset(new EventManager(_stateMachine.get()));

	_renderer.reset(new Renderer(width, height));
	_resourceManager.reset(new ResourceManager(_renderer.get()));
	_entityManager.reset(new EntityManager(_eventManager.get()));
	_systemManager.reset(new SystemManager(_eventManager.get()));
	
	_entityPrototypes.reset(new EntityPrototypes);

	_renderingSystem.reset(
		new firefly::RenderingSystem(this));
	_renderingSystem->setActive(true);
	_systemManager->addSystem(_renderingSystem);
}

Engine::~Engine() {
	SDL_Quit();
}

void Engine::setWindowHeader(const std::string& header) {
	_renderer->setWindowHeader(header);
}

void Engine::setWindowIcon(const std::string& iconPath) {
	_renderer->setWindowIcon(iconPath);
}

int Engine::run() {

	std::shared_ptr<IEvent> updateEvent(new UpdateEvent);
	SDL_Event event;

	// TODO make an option for restricting fps
	// TODO divide to two threads for logic and rendering
	while (_isRunning) {
		while (SDL_PollEvent(&event) != 0) {
			onSDLEvent(event);
		}

		_renderer->clearViewport();

		_eventManager->registerEvent(updateEvent);
		_eventManager->processEvents();
		
		SDL_RenderPresent(_renderer->getContext());
	}
	return _returnCode;
}

void Engine::stop() {
	_isRunning = false;
}
	
bool Engine::isRunning() const {
	return _isRunning;
}

Renderer* Engine::getRenderer() const {
	return _renderer.get();
}

ResourceManager* Engine::getResourceManager() const {
	return _resourceManager.get();
}

EntityManager* Engine::getEntityManager() const {
	return _entityManager.get();
}

EntityPrototypes* Engine::getEntityPrototypes() const {
	return _entityPrototypes.get();
}

SystemManager* Engine::getSystemManager() const {
	return _systemManager.get();
}

EventManager* Engine::getEventManager() const {
	return _eventManager.get();
}

StateMachine* Engine::getStateMachine() const {
	return _stateMachine.get();
}

void Engine::onSDLEvent(const SDL_Event& event) {
	switch (event.type) {
		case SDL_QUIT:
			_isRunning = false;
			break;
		default:
			break;
	}

	std::shared_ptr<IEvent> nativeEvent(new NativeEvent(event));
	_eventManager->registerEvent(std::move(nativeEvent));
}

}
