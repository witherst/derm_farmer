#include <iostream>

#include "headers/game.h"

namespace fd {

	Game::Game()
		: render_window_(sf::VideoMode(640, 480), "Derm Farmer"),
			view_(sf::FloatRect(0.f, 0.f, 640.f, 480.f)) {
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
			case sf::Event::MouseButtonPressed:
				HandlePlayerInput(event.mouseButton.button, true);
				break;
		//	case sf::Event::MouseButtonReleased:
		//		HandlePlayerInput(event.mouseButton.button, false);
		//		break;
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
		main_player_.HandleMovement(delta_time, tmap_, view_);		

		// Update view.
		UpdateView();
	}

	void Game::UpdateView() {
		float view_width = view_.getSize().x;
		float view_height = view_.getSize().y;

		// Check to see if we're near (0,0) or (max_width, max_height) of the map and stop
		//	having the camera follow the player.
		if (ShouldStopViewScrolling(view_width, view_height)) {
			return;
		}	

		// Check if we want to stop vertical scrolling but keep scrolling horizontally.
		if (ShouldStopVerticalScrolling(view_height)) {
			view_.setCenter({main_player_.getPosition().x, view_.getCenter().y});
			return;
		}

		// Check if we want to stop horizontal scrolling but keep scrolling vertically.
		if (ShouldStopHorizontalScrolling(view_width)) {
			view_.setCenter({view_.getCenter().x, main_player_.getPosition().y});
			return;
		}
	
		view_.setCenter(main_player_.getPosition());
		
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


	/*
		Check to see if we should stop view from scrolling horizontally and vertically if we're at the corners of 
		the map.
		TODO: Make this function look better. This seems...messy.
	*/
	bool Game::ShouldStopViewScrolling(const float view_width, const float view_height) {
		float view_width_buffer = view_width / 2.0;
		float view_height_buffer = view_height / 2.0;
		if (main_player_.getPosition().x < view_width_buffer && main_player_.getPosition().y < view_height_buffer ||
			
			main_player_.getPosition().x >= tmap_.GetMapParser()->GetMapWidthInPixels() - view_width_buffer && 
			main_player_.getPosition().y < view_height_buffer ||

			main_player_.getPosition().y >= tmap_.GetMapParser()->GetMapHeightInPixels() - view_height_buffer &&
			main_player_.getPosition().x < view_width_buffer ||

			main_player_.getPosition().x >= tmap_.GetMapParser()->GetMapWidthInPixels() - view_width_buffer && 
			main_player_.getPosition().y >= tmap_.GetMapParser()->GetMapHeightInPixels() - view_height_buffer) {
			return true;
		}
		return false;
	}

	bool Game::ShouldStopHorizontalScrolling(const float view_width) {
		float view_width_buffer = view_width / 2.0;
		if (main_player_.getPosition().x < view_width_buffer ||
			main_player_.getPosition().x >= tmap_.GetMapParser()->GetMapWidthInPixels() - view_width_buffer) {
			return true;
		}
		return false;
	}

	bool Game::ShouldStopVerticalScrolling(const float view_height) {
		float view_height_buffer = view_height / 2.0;
		if (main_player_.getPosition().y < view_height_buffer ||
			main_player_.getPosition().y >= tmap_.GetMapParser()->GetMapHeightInPixels() - view_height_buffer) {
			return true;
		}
		return false;
	}

	void Game::HandlePlayerInput(sf::Keyboard::Key key, bool is_pressed) {
		main_player_.HandleKeyPress(key, is_pressed);
	}

	void Game::HandlePlayerInput(sf::Mouse::Button button, bool is_pressed) {
		main_player_.HandleMouseButtonPress(button, is_pressed, render_window_, view_);
	}

} // namespace fd

