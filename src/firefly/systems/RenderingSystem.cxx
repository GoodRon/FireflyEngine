#include "RenderingSystem.h"

#include <algorithm>

#include <SDL_timer.h>

#include "Entity.h"
#include "Engine.h"
#include "Frame.h"
#include "Renderer.h"

#include "components/Visual.h"
#include "components/Position.h"

namespace firefly {

static bool sortEntities(Entity* lhs, Entity* rhs) {
	if (!lhs || !rhs) {
		return true;
	}

	const auto visualComponentLhs = lhs->getComponent<Visual>();
	const auto visualComponentRhs = rhs->getComponent<Visual>();

	if (!visualComponentLhs || !visualComponentRhs) {
		return true;
	}
	return visualComponentLhs->zIndex < visualComponentRhs->zIndex;
}

static Frame* advanceFrame(Visual* visualComponent, uint64_t timepoint) {
	if (!visualComponent) {
		return nullptr;
	}

	if (visualComponent->states.find(visualComponent->currentState) == 
		visualComponent->states.end()) {
		return nullptr;
	}

	auto& state = visualComponent->states[visualComponent->currentState];
	if (state.frames.empty()) {
		return nullptr;
	}

	if (visualComponent->frameIndex >= state.frames.size()) {
		visualComponent->frameIndex = 0;
	}

	auto& frame = state.frames[visualComponent->frameIndex];
	const auto duration = frame->getDuration();

	if (timepoint < visualComponent->timepoint) {
		visualComponent->timepoint = timepoint;
	}

	const uint64_t elapsedMs = timepoint - visualComponent->timepoint;
	if (elapsedMs < duration) {
		return frame.get();
	}

	visualComponent->timepoint = timepoint + duration - elapsedMs;

	if (visualComponent->frameIndex + 1 >= state.frames.size()) {
		if (state.isLooped) {
			visualComponent->frameIndex = 0;
		} else {
			state.isFinished = true;
		}
	} else {
		visualComponent->frameIndex++;
	}

	frame = state.frames[visualComponent->frameIndex];
	return frame.get();
}

RenderingSystem::RenderingSystem(Engine* engine):
	ISystem("RenderingSystem", engine),
	_renderer(engine->getRenderer()),
	_isRenderListChanged(true),
	_renderList() {

	addRequiredComponent(Visual::ComponentName);
	addRequiredComponent(Position::ComponentName);
}

RenderingSystem::~RenderingSystem() {
}

void RenderingSystem::onUpdate() {
	if (_isRenderListChanged) {
		_renderList.clear();

		auto& entities = getEntities();
		_renderList.reserve(entities.size());

		for (auto& entity: entities) {
			_renderList.push_back(entity.second);
		}

		_isRenderListChanged = false;

		std::sort(_renderList.begin(), _renderList.end(), sortEntities);
	}

	Position* positionComponent = nullptr;
	Visual* visualComponent = nullptr;

	for (auto& entity: _renderList) {
		if (!entity->isActive()) {
			continue;
		}

		positionComponent = entity->getComponent<Position>();
		visualComponent = entity->getComponent<Visual>();

		if (!visualComponent->isVisible) {
			continue;
		}

		draw(positionComponent, visualComponent);
	}
}

bool RenderingSystem::onRegisterEntity(Entity* entity) {
	_isRenderListChanged = true;
	return true;
}

void RenderingSystem::onUnregisterEntity(Entity* entity) {
	_isRenderListChanged = true;
}

void RenderingSystem::draw(Position* positionComponent, 
		Visual* visualComponent) const {
	if (!positionComponent || !visualComponent) {
		return;
	}

	const auto frame = advanceFrame(visualComponent, getLastUpdateTimepoint());
	if (!frame) {
		return;
	}

	// TODO improve
	SDL_Rect source = frame->getSourceRect();
	SDL_Rect dest = positionComponent->toRect();
	SDL_Point center = positionComponent->center();

	_renderer->drawTexture(frame->getTexture(), &source, &dest, 
		positionComponent->direction, &center);
}

}