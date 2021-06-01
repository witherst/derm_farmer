#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "headers/player.h"
#include "headers/resource_holder.h"
#include "headers/resource_identifiers.h"
#include "headers/texture_holder.h"
#include "headers/tile_map.h"

namespace fd {	// Should be the name of the directory we're in.

	class Game
	{
	public:
		Game();
		void LoadResources();
		void Run();
		void SetupEntities();

	private:
		// Internal functions.
		bool ShouldStopViewScrolling(const float width, const float height);
		bool ShouldStopHorizontalScrolling(const float width);
		bool ShouldStopVerticalScrolling(const float height);
		void HandlePlayerInput(sf::Keyboard::Key key, bool is_pressed);
		void ProcessEvents();
		void Render();
		void Update(sf::Time);
		void UpdateView();

		// Member variables.	
		float fps_ = 60.f;
		Player main_player_;
		ResourceHolder<sf::Texture, textures::ID> textures_holder_;
		sf::RenderWindow render_window_;
		sf::Time delta_time_{};
		sf::Time time_per_frame = sf::seconds(1. / fps_);
		sf::View view_;
		TileMap tmap_;	
	};

}	// namespace fd
#endif
