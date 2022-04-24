#include "Quadtree.h"

#include <firefly/Entity.h>
#include <firefly/components/Position.h>

namespace spacewar {

// TODO set these values
constexpr size_t maxLevel = 5;
constexpr size_t maxObjects = 5;

EntityQuadtree::EntityQuadtree(
	const SDL_Rect& boundaries, 
	size_t level):
	_level(0),
	_boundaries(boundaries),
	_entities(),
	_nodes() {

	_nodes.fill(nullptr);
}

EntityQuadtree::~EntityQuadtree() {
	clear();
}

void EntityQuadtree::insert(firefly::Entity* entity) {
	if (!entity) {
		return;
	}

	auto position = entity->getComponent<firefly::Position>();
	if (!position) {
		return;
	}

	if (_nodes[0] != nullptr) {
		const int index = getIndex(position->toRect());

		if (index > -1) {
			_nodes[index]->insert(entity);
			return;
		}
	}

	_entities.push_back(entity);

	if (_entities.size() < maxObjects) {
		return;
	}

	if (_level > maxLevel) {
		return;
	}

	if (_nodes[0] == nullptr) {
		split();
	}

	
	int index = -1;
	firefly::Entity* nodeEntity;

	auto it = _entities.begin();
	while (it != _entities.end()) {

		nodeEntity = *it;

		position = nodeEntity->getComponent<firefly::Position>();
		if (!position) {
			return;
		}

		index = getIndex(position->toRect());
		if (index > - 1) {
			_nodes[index]->insert(nodeEntity);
			it = _entities.erase(it);
			continue;
		}

		++it;
	}
}

std::list<firefly::Entity*> EntityQuadtree::retrieve(
	const SDL_Rect& rect) const {

	const int index = getIndex(rect);
	if (index > -1 && _nodes[0] != nullptr) {
		return _nodes[index]->retrieve(rect);
	}
	return _entities;
}

void EntityQuadtree::clear() {
	_entities.clear();

	for (auto& node: _nodes) {
		if (!node) {
			continue;
		}

		node->clear();
		delete node;
		node = nullptr;
	}
}

void EntityQuadtree::split() {
	if (_nodes[0] != nullptr) {
		return;
	}

	const int nodeWidth = _boundaries.w / 2;
	const int nodeHeight = _boundaries.h / 2;

	_nodes[0] = new EntityQuadtree(SDL_Rect{_boundaries.x, _boundaries.y, 
		nodeWidth, nodeHeight}, _level + 1);
	_nodes[1] = new EntityQuadtree(SDL_Rect{_boundaries.x + nodeWidth, 
		_boundaries.y, nodeWidth, nodeHeight}, _level + 1);
	_nodes[2] = new EntityQuadtree(SDL_Rect{_boundaries.x + nodeWidth, 
		_boundaries.y + nodeHeight, nodeWidth, nodeHeight}, _level + 1);
	_nodes[3] = new EntityQuadtree(SDL_Rect{_boundaries.x, 
		_boundaries.y + nodeHeight, nodeWidth, nodeHeight}, _level + 1);
}

int EntityQuadtree::getIndex(const SDL_Rect& rect) const {
	const int verticalCenter = _boundaries.x + (_boundaries.w / 2);
	const int horizontalCenter = _boundaries.y + (_boundaries.h / 2);

	const bool topHalf = (rect.y + rect.h < horizontalCenter);
	const bool bottomHalf = (rect.y > horizontalCenter);

	if (!topHalf && !bottomHalf) {
		return -1;
	}

	const bool leftHalf = rect.x + rect.w < verticalCenter;
	const bool rightHalf = rect.x > verticalCenter;

	if (!leftHalf && !rightHalf) {
		return -1;
	}

	if (leftHalf && topHalf) {
		return 0;
	}

	if (rightHalf && topHalf) {
		return 1;
	}

	if (rightHalf && bottomHalf) {
		return 2;
	}

	if (leftHalf && bottomHalf) {
		return 3;
	}
	return -1;
}

}
