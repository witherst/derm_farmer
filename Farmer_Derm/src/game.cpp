#include <iostream>

#include "headers/game.h"

namespace fd {

	Game::Game()
		: render_window_(sf::VideoMode(640, 480), "Derm Farmer"),
		player_(),
		view_(sf::FloatRect(0.f, 0.f, 640.f, 480.f)) {
	}

	void Game::Run()
	{
		sf::Clock clock;
		sf::Time time_since_last_update = sf::Time::Zero;
 	
		textures_.Load(textures::ID::Player, "assets/art/pixil/derm/derm_37x49.png");
		textures_.Load(textures::ID::MapPng, "assets/art/aseprite/landscape/landscape_sheet.png");

		tmap_.Load(textures_.Get(textures::ID::MapPng), "assets/art/tiled/map/farm_map.tmx");

		player_.setTexture(textures_.Get(textures::ID::Player));
		player_.setOrigin(player_.getLocalBounds().width / 2.f, player_.getLocalBounds().height / 2.f);
		player_.setPosition(view_.getSize().x / 2., view_.getSize().y / 2.);
		player_.setScale(1.f, 1.f);

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

	void Game::ProcessEvents() {
		sf::Event event;
		while (render_window_.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Resized:	// So sprites don't get stretched.
				view_.setSize(event.size.width, event.size.height);
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
		float width = view_.getSize().x;
		float height = view_.getSize().y;
		sf::Vector2f movement(0.f, 0.f);
		float distance_to_move = 10.f;

		if (is_moving_up_ && player_.getPosition().y >= 0.0 + player_.getTextureRect().height / 2.0) {
			movement.y -= distance_to_move;
		}
		if (is_moving_down_) {
			movement.y += distance_to_move;
		}
		if (is_moving_left_ && player_.getPosition().x >= 0.0 + player_.getTextureRect().width / 2.0) {
			movement.x -= distance_to_move;
		}
		if (is_moving_right_) {
			movement.x += distance_to_move;
		}

		player_.move(movement * delta_time.asSeconds());
		// Stop view from scrolling if we're at the edges of the map.	
		if (player_.getPosition().x < width / 2.0 && player_.getPosition().y < height / 2.0) {
			return;
		}
		else if (player_.getPosition().x >= width / 2.0 && player_.getPosition().y >= height / 2.0) {
			view_.setCenter(player_.getPosition());	
		}
		else if (player_.getPosition().x < width / 2.0) {
			view_.setCenter({view_.getCenter().x, player_.getPosition().y});
		}
		else {
			view_.setCenter({player_.getPosition().x, view_.getCenter().y});
		}

			
	}

	void Game::Render() {
		render_window_.clear();
		render_window_.setView(view_);
		render_window_.draw(tmap_);
		render_window_.draw(player_);
		render_window_.display();
	}

	void Game::HandlePlayerInput(sf::Keyboard::Key key, bool is_pressed) {
		if (key == sf::Keyboard::W) {
			is_moving_up_ = is_pressed;
		}
		else if (key == sf::Keyboard::S) {
			is_moving_down_ = is_pressed;
		}
		else if (key == sf::Keyboard::A) {
			is_moving_left_ = is_pressed;
		}
		else if (key == sf::Keyboard::D) {
			is_moving_right_ = is_pressed;
		}
	}

} // namespace fd

