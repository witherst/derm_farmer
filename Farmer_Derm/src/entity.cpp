#include "headers/entity.h"
#include <iostream>

namespace fd {
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

	void Entity::HandleMovement(const sf::Time delta_time) {
		sf::Vector2f movement(0.f, 0.f);

		if (is_moving_up_ && sprite_.getPosition().y >= 0.0 + sprite_.getTextureRect().height / 2.0) {
			movement.y -= GetMovementSpeed();	
		}
		if (is_moving_down_) {
			movement.y += GetMovementSpeed();
		}
		if (is_moving_left_ && sprite_.getPosition().x >= 0.0 + sprite_.getTextureRect().width / 2.0) {
			movement.x -= GetMovementSpeed();
		}
		if (is_moving_right_) {
			movement.x += GetMovementSpeed();
		}
		sprite_.move(movement * delta_time.asSeconds());
	}

	void Entity::SetMovementSpeed(const float distance) {
		speed_ = distance;
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
	}

	void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		// Apply the transform.
		states.transform *= getTransform();

		// Apply the tileset texture.
		states.texture = &texture_;
		
		// Draw the layers
		target.draw(sprite_, states);	
	}

}	// namespace fd

