#include <iostream>

#include "headers/game.h"

namespace fd {

	Game::Game()
		: render_window_(sf::VideoMode(640, 480), "Derm Farmer"),
			player_(), view_(sf::FloatRect(0.f, 0.f, 640.f, 480.f)) {
		LoadResources();
		SetupEntities();
	}	

	void Game::Run()
	{
		sf::Clock clock;
		sf::Time time_since_last_update = sf::Time::Zero;	

		while (render_window_.isOpen()) {
			time_since_last_update = clock.restart();
			while (time_since_last_update <= time_per_frame) {
				time_since_last_update -= time_per_frame;
				ProcessEvents();
				Update(time_per_frame);
				Render();	
			}
		}
	}

	void Game::LoadResources() {
		textures_holder_.Load(textures::ID::Player, "assets/art/pixil/derm/derm_37x49.png");
		textures_holder_.Load(textures::ID::MapPng, "assets/art/aseprite/landscape/landscape_sheet.png");
		tmap_.Load(textures_holder_.Get(textures::ID::MapPng), "assets/art/tiled/map/farm_map.tmx");
	}

	void Game::SetupEntities() {
		main_player_.SetupEntity(textures_holder_, view_);	
	}

	void Game::ProcessEvents() {
		sf::Event event;
		while (render_window_.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Resized:	// So sprites don't get stretched.
				view_.setSize(event.size.width, event.size.height);
				view_.setCenter(event.size.width / 2, event.size.height / 2);
				render_window_.setView(view_);
				break;
			case sf::Event::KeyPressed:
				HandlePlayerInput(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				HandlePlayerInput(event.key.code, false);
				break;
			case sf::Event::Closed:
				render_window_.close();
				return;
				break;
			}
		}
	}

	void Game::Update(sf::Time delta_time) {
		delta_time_ = delta_time;	

		// Update main player's movement.
		main_player_.HandleMovement(delta_time, tmap_);		

		// Update view.
		UpdateView();
	}

	void Game::UpdateView() {
		// Stop view from scrolling if we're at the edges of the map.	
		float width = view_.getSize().x;
		float height = view_.getSize().y;
		if (main_player_.getPosition().x < width / 2.0 && main_player_.getPosition().y < height / 2.0) {
			return;
		}
		else if (main_player_.getPosition().x >= width / 2.0 && main_player_.getPosition().y >= height / 2.0) {
			view_.setCenter(main_player_.getPosition());	
		}
		else if (main_player_.getPosition().x < width / 2.0) {
			view_.setCenter({view_.getCenter().x, main_player_.getPosition().y});
		}
		else {
			view_.setCenter({main_player_.getPosition().x, view_.getCenter().y});
		}	

	}

	void Game::Render() {
		render_window_.clear();
		render_window_.setView(view_);

		// Draw map.
		render_window_.draw(tmap_);

		// Draw player.
		render_window_.draw(main_player_);

		// Display.
		render_window_.display();
	}

	void Game::HandlePlayerInput(sf::Keyboard::Key key, bool is_pressed) {
		main_player_.HandleKeyPress(key, is_pressed);
	}

} // namespace fd

