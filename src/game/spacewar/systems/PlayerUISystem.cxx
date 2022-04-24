#include "PlayerUISystem.h"

#include <forward_list>
#include <sstream>

#include <firefly/Engine.h>
#include <firefly/Renderer.h>
#include <firefly/Entity.h>
#include <firefly/components/Player.h>
#include <firefly/components/Ammunition.h>
#include <firefly/components/Lives.h>
#include <firefly/components/Fuel.h>

#include "misc/UIHelpers.h"

#include "WeaponId.h"

namespace spacewar {

PlayerUISystem::PlayerUISystem(firefly::Engine* engine):
	firefly::ISystem(PlayerUISystem::Name, engine),
	_renderer(engine->getRenderer()) {

	addRequiredComponent(firefly::Player::ComponentName);
}

PlayerUISystem::~PlayerUISystem() {
}

void PlayerUISystem::onUpdate() {
	for (auto& entity: getEntities()) {
		drawPlayerUI(entity.second);
	}
}

void PlayerUISystem::drawPlayerUI(
	firefly::Entity* entity) const {

	if (!entity) {
		return;
	}

	firefly::TexturePointer label;
	std::forward_list<firefly::TexturePointer> labels;

	const auto player = entity->getComponent<firefly::Player>();
	if (!player) {
		return;
	}

	const auto ammunition = entity->getComponent<firefly::Ammunition>();
	if (ammunition) {
		labels.push_front(std::move(drawAmmunition(ammunition)));
	}

	const auto fuel = entity->getComponent<firefly::Fuel>();
	if (fuel) {
		labels.push_front(std::move(drawFuel(fuel)));
	}

	const auto lives = entity->getComponent<firefly::Lives>();
	if (lives) {
		labels.push_front(std::move(drawLives(lives)));
	}

	labels.push_front(std::move(drawPlayer(player)));

	constexpr int heightSpace = 0;
	SDL_Rect uiRect{0, 0, 0, 0};

	for (auto& label: labels) {
		const auto textureRect = _renderer->getTextureRect(label);

		if (textureRect.w > uiRect.w) {
			uiRect.w = textureRect.w;
		}
		uiRect.h += textureRect.h + heightSpace;
	}

	const auto screenRect = _renderer->getViewport();
	setUIPosition(player->playerId, uiRect, screenRect);

	SDL_Rect destinationRect;
	SDL_Rect textureRect;
	int offsetY = 0;

	for (auto& label: labels) {
		textureRect = _renderer->getTextureRect(label);
		destinationRect = textureRect;
		destinationRect.x = uiRect.x;
		destinationRect.y = uiRect.y + offsetY;

		// TODO move from here
		_renderer->drawTexture(label, &textureRect, &destinationRect);

		offsetY += textureRect.h + heightSpace;
	}
}

// TODO cache somehow
firefly::TexturePointer PlayerUISystem::drawPlayer(
	firefly::Player* player) const {

	if (!player) {
		return nullptr;
	}

	std::stringstream stream;
	stream << "Player: ";
	stream << player->playerName;

	const int fontSize = 20;
	const SDL_Color color{0xf1, 0xf1, 0xf1, 255};
	return _renderer->drawText(stream.str(), fontSize, color);
}

firefly::TexturePointer PlayerUISystem::drawLives(
	firefly::Lives* lives) const {

	if (!lives) {
		return nullptr;
	}

	std::stringstream stream;
	stream << "Lives ";
	stream << lives->currentLives;

	const int fontSize = 20;
	const SDL_Color color{0xf1, 0xf1, 0xf1, 255};
	return _renderer->drawText(stream.str(), fontSize, color);
}

firefly::TexturePointer PlayerUISystem::drawFuel(
	firefly::Fuel* fuel) const {
	
	if (!fuel) {
		return nullptr;
	}

	std::stringstream stream;
	stream.precision(3);
	stream << "Fuel ";
	stream << fuel->current;
	stream << "%";

	const int fontSize = 20;
	const SDL_Color color{0xf1, 0xf1, 0xf1, 255};
	return _renderer->drawText(stream.str(), fontSize, color);
}

firefly::TexturePointer PlayerUISystem::drawAmmunition(
	firefly::Ammunition* ammunition) const {

	if (!ammunition) {
		return nullptr;
	}

	std::stringstream stream;
	stream << "Rockets ";

	if (ammunition->weapons.find(WeaponId::RocketLauncher) !=
		ammunition->weapons.end()) {

		stream << ammunition->weapons[WeaponId::RocketLauncher].rounds;
	}

	const int fontSize = 20;
	const SDL_Color color{0xf1, 0xf1, 0xf1, 255};
	return _renderer->drawText(stream.str(), fontSize, color);
}

}
