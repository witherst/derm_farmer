#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "headers/resource_holder.h"
#include "headers/resource_identifiers.h"
#include "headers/texture_holder.h"
#include "headers/tile_map.h"

namespace fd {	// Should be the name of the directory we're in.

	class Game
	{
	public:
		Game();
		void Run();

	private:
		// Internal functions.
		void HandlePlayerInput(sf::Keyboard::Key, bool);
		void ProcessEvents();
		void Render();
		void Update(sf::Time);

		// Member variables.
		bool is_moving_up_{};
		bool is_moving_down_{};
		bool is_moving_left_{};
		bool is_moving_right_{};
		float fps_ = 60.f;
		ResourceHolder<sf::Texture, textures::ID> textures_;
		sf::Sprite player_;
		sf::RenderWindow render_window_;
		sf::Time time_per_frame = sf::seconds(1. / fps_);
		sf::View view_;
		TileMap tmap_;
	};

}	// namespace fd
#endif
