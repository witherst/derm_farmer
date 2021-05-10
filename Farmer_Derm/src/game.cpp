#include <iostream>

#include "headers/game.h"
#include "headers/resource_holder.h"
#include "headers/resource_identifiers.h"
#include "headers/texture_holder.h"

namespace fd {

	Game::Game()
		: render_window_(sf::VideoMode(640, 480), "Derm Farmer"),
		player_(),
		view_(sf::FloatRect(0.f, 0.f, 640.f, 480.f))
	{
		render_window_.setView(view_);
	}

	void Game::Run()
	{
		sf::Clock clock;
		sf::Time time_since_last_update = sf::Time::Zero;

		ResourceHolder<sf::Texture, textures::ID> textures;
		textures.Load(textures::ID::Player, "assets/art/pixil/derm/derm_37x49.png");

		player_.setTexture(textures.Get(textures::ID::Player));
		player_.setOrigin(player_.getLocalBounds().width / 2.f, player_.getLocalBounds().height / 2.f);
		player_.setPosition(100.f, 100.f);
		player_.setScale(3.f, 3.f);

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
		sf::Vector2f movement(0.f, 0.f);
		float distance_to_move = 5.f;
		if (is_moving_up_) {
			movement.y -= distance_to_move;
		}
		else if (is_moving_down_) {
			movement.y += distance_to_move;
		}
		else if (is_moving_left_) {
			movement.x -= distance_to_move;
		}
		else if (is_moving_right_) {
			movement.x += distance_to_move;
		}

		player_.move(movement * delta_time.asSeconds());
	}

	void Game::Render() {
		render_window_.clear();
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

