/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef FIREFLY_RENDERER_H
#define FIREFLY_RENDERER_H

#include <memory>
#include <string>

#include <SDL_rect.h>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

namespace firefly {

using TexturePointer = std::shared_ptr<SDL_Texture>;

class Renderer {
public:
	Renderer(int width, int heigh);
	~Renderer();

	Renderer(const Renderer& other) = delete;
	Renderer& operator=(Renderer& other) = delete;

	void setWindowHeader(const std::string& header);
	void setWindowIcon(const std::string& iconPath);

	bool clearViewport();

	bool drawTexture(const TexturePointer& texture, SDL_Rect* source = nullptr,
					 SDL_Rect* destination = nullptr);

	bool drawTexture(const TexturePointer& texture, SDL_Rect* source,
					 SDL_Rect* destination, double angle, SDL_Point* center);

	bool drawTextureOnTexture(
		const TexturePointer& sourceTexture, 
		const TexturePointer& destinationTexture,
		SDL_Rect* source, SDL_Rect* destination);

	TexturePointer drawText(
		const std::string& message, int fontSize, 
		SDL_Color color, const std::string& fontName = "") const;

	SDL_Rect getTextureRect(const TexturePointer& texture) const;

	bool clearTexture(TexturePointer& texture);

	SDL_Renderer* getContext() const;

	SDL_Rect getViewport() const;

	void setViewport(const SDL_Rect& viewport);

private:
	std::shared_ptr<SDL_Window> _window;
	std::shared_ptr<SDL_Renderer> _renderer;
	SDL_Rect _viewport;
};

}

#endif // FIREFLY_RENDERER_H
