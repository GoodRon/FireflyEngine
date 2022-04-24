/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_MISC_QUADTREE_H
#define SW_MISC_QUADTREE_H

#include <SDL_rect.h>

#include <list>
#include <array>

namespace firefly {
	class Entity;
}

namespace spacewar {

class EntityQuadtree {
public:
	EntityQuadtree(const SDL_Rect& boundaries, size_t level = 0);
	~EntityQuadtree();

	EntityQuadtree(const EntityQuadtree&) = delete;
	EntityQuadtree& operator=(const EntityQuadtree&) = delete;

	void insert(firefly::Entity* entity);
	std::list<firefly::Entity*> retrieve(const SDL_Rect& rect) const;

	void clear();

private:
	void split();
	int getIndex(const SDL_Rect& rect) const;

private:
	size_t _level;
	SDL_Rect _boundaries;
	std::list<firefly::Entity*> _entities;
	std::array<EntityQuadtree*, 4> _nodes;
};

}

#endif // SW_MISC_QUADTREE_H
