#include "headers/entity.h"
#include "headers/utility/vector2.h"
#include <iostream>

namespace fd {
	void Entity::HandleCollisions(TileMap& tmap) {
		// Check for collision against our collision set.
		std::string player_tile = tmap.MakeTileKey(floor(getPosition().x / tmap.GetMapParser()->GetTileWidthInPixels()),
												   floor(getPosition().y / tmap.GetMapParser()->GetTileHeightInPixels()));
		if (tmap.GetCollisionSet()->count(player_tile) > 0) {
			setPosition(player_last_good_pos_);
			return;
		}
	}

	void Entity::HandleKeyPress(const sf::Keyboard::Key key, const bool is_pressed) {
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

	void Entity::HandleMouseButtonRelease(const sf::Mouse::Button button, const bool is_pressed, const sf::RenderWindow& window, const sf::View& view) {
		if (button == sf::Mouse::Button::Right) {
			// If the view is not centered (i.e., if the view has been scrolled right or down), we have to offset the waypoint
			// by the amount that has been scrolled.
			int x_offset = view.getCenter().x - (view.getSize().x / 2);
			int y_offset = view.getCenter().y - (view.getSize().y / 2);
			if (waypoints_.size() > 0) {
				waypoints_[0] = { sf::Mouse::getPosition(window).x + x_offset, sf::Mouse::getPosition(window).y + y_offset };
			}
			else {
				waypoints_.push_back({ sf::Mouse::getPosition(window).x + x_offset, sf::Mouse::getPosition(window).y + y_offset });
			}
			AnimatePlayer();
		}
	}

	void Entity::HandleMovement(const sf::Time delta_time, TileMap& tmap, const sf::View& view) {
		sf::Vector2f movement(0.f, 0.f);
		float width_buffer = view.getSize().x / 2.0;
		float height_buffer = view.getSize().y / 2.0;
		float sprite_half_height_buffer = sprite_.getTextureRect().height / 2.0;
		float sprite_half_width_buffer = sprite_.getTextureRect().width / 2.0;

		if (is_moving_up_ && getPosition().y >= 0.0 + sprite_half_height_buffer) {
			movement.y -= GetMovementSpeed();	
		}
		if (is_moving_down_ && getPosition().y <= tmap.GetMapParser()->GetMapHeightInPixels() - sprite_half_height_buffer) {
			movement.y += GetMovementSpeed();
		}
		if (is_moving_left_ && getPosition().x >= 0.0 + sprite_half_width_buffer) {
			movement.x -= GetMovementSpeed();
		}
		if (is_moving_right_ && getPosition().x <= tmap.GetMapParser()->GetMapWidthInPixels() - sprite_half_width_buffer) {
			movement.x += GetMovementSpeed();
		}
		move(movement * delta_time.asSeconds());
		
		// Check and handle collisions.
		HandleCollisions(tmap);

		// Set last good position of the player.
		player_last_good_pos_ = getPosition();
	}

	void Entity::SetMovementSpeed(const float speed) {
		speed_ = speed;
	}

	void Entity::SetTexture(sf::Texture& texture) {
		texture_ = texture;
	}

	void Entity::SetSpriteTexture(sf::Texture& texture) {
		sprite_.setTexture(texture);
	}

	void Entity::SetupEntity(ResourceHolder<sf::Texture, textures::ID>& resource_holder, sf::View& view) {
		SetTexture(resource_holder.Get(textures::ID::Player));
		SetSpriteTexture(resource_holder.Get(textures::ID::Player));
		SetInitialTransforms(view);
	}

	void Entity::SetInitialTransforms(sf::View& view) {
		setOrigin(sprite_.getLocalBounds().width / 2.f, sprite_.getLocalBounds().height / 2.f);
		setPosition(view.getSize().x / 2., view.getSize().y / 2.);
		player_last_good_pos_ = getPosition();
	}	

	void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		// Apply the transform.
		states.transform *= getTransform();

		// Apply the tileset texture.
		states.texture = &texture_;
		
		// Draw the layers
		target.draw(sprite_, states);
		DrawLines(waypoints_, getPosition(), target);	
		
	}

	void Entity::DrawLines(const std::vector<sf::Vector2i>& waypoints, const sf::Vector2f& player_position, sf::RenderTarget& target) const {
		for (auto& waypoint : waypoints) {
			sf::Vertex line[] = {
				sf::Vertex(player_position),
				sf::Vertex(sf::Vector2f(waypoint))
			};
			target.draw(line, 2, sf::Lines);
		}
	}

	void Entity::AnimatePlayer() {
		//if (waypoints_.size() > 0) {
		//	setPosition(float(waypoints_[0].x), float(waypoints_[0].y));
		//}
	}

	void Entity::MoveToWaypoint(const sf::Time delta_time) {
		if (waypoints_.size() > 0) {
			VECTOR2 util_player_pos(getPosition().x, getPosition().y);
			VECTOR2 util_mouse_pos(waypoints_[0].x, waypoints_[0].y);
			VECTOR2 util_dir = util_mouse_pos - util_player_pos;
			// util_dir = util_dir.norm();
			sf::Vector2f dir = util_dir.sf();
			move(dir * delta_time.asSeconds() * 0.01f);
		}
	}

	/*
		Update will handle everything related to updating the entity
		on this time step.
	*/
	void Entity::Update(const sf::Time delta_time, TileMap& tilemap, const sf::View& view) {
		MoveToWaypoint(delta_time);
	}
}	// namespace fd

