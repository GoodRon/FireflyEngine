/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include <iostream>
#include <fstream>
#include <sstream>

#include <SDL.h>
#include <SDL_image.h>

#include "ResourceManager.h"
#include "Renderer.h"

namespace firefly {

ResourceManager::ResourceManager(Renderer* renderer) :
	_renderer(renderer),
	_textureCache() {
}

ResourceManager::~ResourceManager() {
}

TexturePointer ResourceManager::loadTexture(const std::string& name) {
	if (_textureCache.find(name) != _textureCache.end()) {
		return _textureCache.at(name);
	}

	if (!_renderer) {
		return nullptr;
	}

	SDL_Surface* surface = IMG_Load(name.c_str());
	if (surface == nullptr) {
		return nullptr;
	}

	auto texture = SDL_CreateTextureFromSurface(_renderer->getContext(),
												surface);
	if (texture == nullptr) {
		SDL_FreeSurface(surface);
		return nullptr;
	}

	SDL_FreeSurface(surface);

	TexturePointer ptr(texture, SDL_DestroyTexture);
	_textureCache.emplace(name, ptr);
	return ptr;
}

void ResourceManager::freeUnused() {
	for (auto texture = _textureCache.begin(); 
		texture != _textureCache.end(); ++texture) {
		if ((*texture).second.use_count() <= 1) {
			_textureCache.erase(texture);
		}
	}
}

void ResourceManager::clear() {
	_textureCache.clear();
}

}
