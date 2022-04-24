#include "UIHelpers.h"

namespace spacewar {

// TODO improve it
void setUIPosition(int playerId, SDL_Rect& uiRect,
	const SDL_Rect& screenRect) {

	constexpr int spaceWidth = 30;
	constexpr int spaceHeight = 30;

	if (playerId == 1) {
		uiRect.x = spaceWidth;
		uiRect.y = screenRect.h - (spaceHeight + uiRect.h);
		return;
	}

	if (playerId == 2) {
		uiRect.x = screenRect.w - (spaceWidth + uiRect.w);
		uiRect.y = spaceHeight;
		return;
	}
}

}