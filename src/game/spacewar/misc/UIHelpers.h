/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_MISC_PLAYER_HELPERS_H
#define SW_MISC_PLAYER_HELPERS_H

#include <string>

#include <SDL_rect.h>

namespace spacewar {

void setUIPosition(int playerId, SDL_Rect& uiRect, 
	const SDL_Rect& screenRect);

}

#endif // SW_MISC_PLAYER_HELPERS_H
