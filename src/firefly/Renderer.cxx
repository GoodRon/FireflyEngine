/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#include "Renderer.h"
#include "EngineException.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

namespace firefly {

const std::string engineName("Firefly Engine");

static bool hasIntersection(
	const SDL_Rect& lhs, const SDL_Rect& rhs) {

	if (lhs.x < rhs.x + rhs.w &&
		lhs.x + lhs.w > rhs.x &&
		lhs.y < rhs.y + rhs.h &&
		lhs.y + lhs.h > rhs.y) {
		return true;
	}
	return false;
}

Renderer::Renderer(int width, int height) :
	_window(nullptr),
	_renderer(nullptr),
	_viewport({0, 0, width, height}) {

	auto window = SDL_CreateWindow(engineName.c_str(),
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		_viewport.w, _viewport.h, SDL_WINDOW_SHOWN);

	if (window == nullptr) {
		throw EngineException(SDL_GetError());
	}

	_window.reset(window, SDL_DestroyWindow);

	auto renderer = SDL_CreateRenderer(_window.get(), -1, 
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (renderer == nullptr) {
		_window.reset();
		throw EngineException(SDL_GetError());
	}
	_renderer.reset(renderer, SDL_DestroyRenderer);

	if (TTF_Init() != 0) {
		// TODO log error
	}

}

Renderer::~Renderer() {
	if (TTF_WasInit()) {
		TTF_Quit();
	}

	_renderer.reset();
	_window.reset();
}

void Renderer::setWindowHeader(const std::string& header) {
	SDL_SetWindowTitle(_window.get(), header.c_str());
}

void Renderer::setWindowIcon(const std::string& iconPath) {
	SDL_Surface* surface = IMG_Load(iconPath.c_str());
	if (!surface) {
		return;
	}

	SDL_SetWindowIcon(_window.get(), surface);
	SDL_FreeSurface(surface);
}

bool Renderer::clearViewport() {
	if (SDL_RenderClear(_renderer.get()) != 0) {
		return false;
	}
	return true;
}

bool Renderer::drawTexture(const TexturePointer& texture, 
	SDL_Rect* source, SDL_Rect* destination) {

	// TODO check if texture is inside the viewport
	if (SDL_RenderCopy(_renderer.get(), texture.get(), source, destination) != 0) {
		return false;
	}
	return true;
}

bool Renderer::drawTexture(const TexturePointer& texture, 
	SDL_Rect* source, SDL_Rect* destination, double angle,
	SDL_Point* center) {

	// TODO check if texture is inside the viewport
	// TODO pass flip

	if (SDL_RenderCopyEx(_renderer.get(), texture.get(), source, destination,
		angle, center, SDL_FLIP_NONE) != 0) {
		return false;
	}
	return true;
}

bool Renderer::drawTextureOnTexture(
	const TexturePointer& sourceTexture,
	const TexturePointer& destinationTexture, 
	SDL_Rect* source, SDL_Rect* destination) {

	if ((!sourceTexture) || (!destinationTexture)) {
		return false;
	}

	SDL_Texture* screen = SDL_GetRenderTarget(_renderer.get());
	SDL_SetRenderTarget(_renderer.get(), destinationTexture.get());
	bool ret = drawTexture(sourceTexture, source, destination);
	SDL_SetRenderTarget(_renderer.get(), screen);
	return ret;
}

TexturePointer Renderer::drawText(
	const std::string& message, int fontSize, 
	SDL_Color color, const std::string& fontName) const {

	if (!TTF_WasInit()) {
		return nullptr;
	}

	if (message.empty() || fontSize <= 0) {
		return nullptr;
	}

	TTF_Font* font = nullptr;
	if (!fontName.empty()) {
		font = TTF_OpenFont(fontName.c_str(), fontSize);
	} else {
		// TODO move from here
		const std::string defaultFont("resources/default.ttf");
		font = TTF_OpenFont(defaultFont.c_str(), fontSize);
	}

	if (font == nullptr){
		// TODO log error
		return nullptr;
	}

	SDL_Surface* surface = TTF_RenderText_Blended(
		font, message.c_str(), color);
	if (surface == nullptr){
		TTF_CloseFont(font);
		return nullptr;
	}

	SDL_Texture* messageTexture = 
		SDL_CreateTextureFromSurface(_renderer.get(), surface);
	if (messageTexture == nullptr) {
		SDL_FreeSurface(surface);
		TTF_CloseFont(font);
		return nullptr;
	}

	TexturePointer texture(messageTexture, SDL_DestroyTexture);

	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
	return texture;
}

SDL_Rect Renderer::getTextureRect(
	const TexturePointer& texture) const {
	
	SDL_Rect rect{0, 0, 0, 0};
	if (!texture) {
		return rect;
	}

	SDL_QueryTexture(
		texture.get(), nullptr, nullptr, &rect.w, &rect.h);
	return rect;
}

bool Renderer::clearTexture(TexturePointer& texture) {
	SDL_Texture* screen = SDL_GetRenderTarget(_renderer.get());
	SDL_SetRenderTarget(_renderer.get(), texture.get());
	bool ret = clearViewport();
	SDL_SetRenderTarget(_renderer.get(), screen);
	return ret;
}

SDL_Renderer* Renderer::getContext() const {
	return _renderer.get();
}

SDL_Rect Renderer::getViewport() const {
	return _viewport;
}

void Renderer::setViewport(const SDL_Rect& viewport) {
	// TODO resize
	_viewport = viewport;
}

}
