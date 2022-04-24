/*
 * Copyright (c) 2022, Roman Meita <theshrodingerscat@gmail.com>
 * All rights reserved
 */

#ifndef SW_SYSTEMS_PLAYER_UI_H
#define SW_SYSTEMS_PLAYER_UI_H

#include <firefly/systems/ISystem.h>

struct SDL_Texture;

namespace firefly {
	class Entity;
	class Renderer;
	class Player;
	class Lives;
	class Fuel;
	class Ammunition;
	using TexturePointer = std::shared_ptr<SDL_Texture>;
}

namespace spacewar {

class PlayerUISystem final: public firefly::ISystem {
public:
	inline static const std::string Name = "PlayerUISystem";

	PlayerUISystem(firefly::Engine* engine);
	~PlayerUISystem() override;

	PlayerUISystem(const PlayerUISystem&) = delete;
	PlayerUISystem& operator=(const PlayerUISystem&) = delete;
	
private:
	void onUpdate() override;
	void drawPlayerUI(firefly::Entity* entity) const;

	firefly::TexturePointer drawPlayer(
		firefly::Player* player) const;
	firefly::TexturePointer drawLives(
		firefly::Lives* lives) const;
	firefly::TexturePointer drawAmmunition(
		firefly::Ammunition* ammunition) const;
	firefly::TexturePointer drawFuel(
		firefly::Fuel* fuel) const;

private:
	firefly::Renderer* const _renderer;
};

}

#endif // SW_SYSTEMS_PLAYER_UI_H
