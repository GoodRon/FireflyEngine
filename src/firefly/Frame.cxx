#include "Frame.h"

namespace firefly {

Frame::Frame(const TexturePointer& texture, 
	const SDL_Rect& sourceRect,
	uint64_t durationMs): 
	_texture(texture),
	_sourceRect(sourceRect),
	_durationMs(durationMs) {
}

Frame::~Frame() {
}

TexturePointer Frame::getTexture() const {
	return _texture;
}

SDL_Rect Frame::getSourceRect() const {
	return _sourceRect;
}

uint64_t Frame::getDuration() const {
	return _durationMs;
}

}
