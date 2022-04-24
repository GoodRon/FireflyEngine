/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_SYSTEMS_ANIMATION_H
#define FIREFLY_SYSTEMS_ANIMATION_H

#include <mutex>
#include <vector>
#include <atomic>

#include "ISystem.h"

namespace firefly {

class Renderer;
class Position;
class Visual;

class RenderingSystem final: public ISystem {
public:
	RenderingSystem(Engine* engine);
	~RenderingSystem() override;

	RenderingSystem(const RenderingSystem&) = delete;
	RenderingSystem& operator=(const RenderingSystem&) = delete;
	
private:
	void onUpdate() override;

	bool onRegisterEntity(Entity* entity) override;
	void onUnregisterEntity(Entity* entity) override;

	void draw(Position* positionComponent, 
		Visual* visualComponent) const;

private:
	Renderer* const _renderer;
	bool _isRenderListChanged;
	std::vector<Entity*> _renderList;
};

}

#endif // FIREFLY_SYSTEMS_ANIMATION_H
