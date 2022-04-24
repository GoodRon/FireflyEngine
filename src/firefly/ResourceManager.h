/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_RESOURCE_MANAGER_H
#define FIREFLY_RESOURCE_MANAGER_H

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

struct SDL_Texture;

namespace firefly {

class Renderer;

using TexturePointer = std::shared_ptr<SDL_Texture>;

class ResourceManager {
public:
	ResourceManager(Renderer* renderer);
	~ResourceManager();

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&) = delete;

	TexturePointer loadTexture(const std::string& name);

	void freeUnused();

	void clear();

private:
	Renderer* _renderer;
	std::unordered_map<std::string, TexturePointer> _textureCache;
};

}

#endif // FIREFLY_RESOURCE_MANAGER_H
