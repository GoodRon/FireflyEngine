/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_ENGINE_H
#define FIREFLY_ENGINE_H

#include <SDL.h>

#include <string>
#include <memory>
#include <atomic>

namespace firefly {

class Renderer;
class ResourceManager;
class EntityPrototypes;
class EntityManager;
class SystemManager;
class EventManager;
class RenderingSystem;
class StateMachine;

class Engine {
public:
	Engine(int width, int height);
	~Engine();
	
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine& other) = delete;

	void setWindowHeader(const std::string& header);
	void setWindowIcon(const std::string& iconPath);

	int run();
	void stop();

	bool isRunning() const;

	Renderer* getRenderer() const;
	ResourceManager* getResourceManager() const;
	EntityManager* getEntityManager() const;

	EntityPrototypes* getEntityPrototypes() const;
	
	SystemManager* getSystemManager() const;
	EventManager* getEventManager() const;

	StateMachine* getStateMachine() const;

private:
	void onSDLEvent(const SDL_Event& event);

private:
	std::atomic<bool> _isRunning;
	int _returnCode;
	std::unique_ptr<Renderer> _renderer;
	std::unique_ptr<ResourceManager> _resourceManager;
	std::unique_ptr<EntityManager> _entityManager;
	std::unique_ptr<EntityPrototypes> _entityPrototypes;
	std::unique_ptr<SystemManager> _systemManager;
	std::unique_ptr<EventManager> _eventManager;
	std::shared_ptr<RenderingSystem> _renderingSystem;
	std::shared_ptr<StateMachine> _stateMachine;
};

}

#endif // FIREFLY_ENGINE_H
