#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include "headers/resource_holder.h"
#include "headers/resource_identifiers.h"

namespace fd {

	class Entity : public sf::Drawable, public sf::Transformable {
	public:
		const sf::Texture& GetTexture() const { return texture_; };
		const sf::Sprite& GetSprite() const { return sprite_; }	
		const float GetMovementSpeed() const { return speed_; }
		void HandleKeyPress(const sf::Keyboard::Key key, const bool is_pressed);
		void HandleMovement(const sf::Time delta_time);
		void SetMovementSpeed(const float distance);
		void SetTexture(sf::Texture& texture);	
		void SetSpriteTexture(sf::Texture& texture);
		void SetupEntity(ResourceHolder<sf::Texture, textures::ID>& resource_holder, sf::View& view);
		void SetInitialTransforms(sf::View& view);
		void UpdatePosition();

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		
		bool is_moving_up_{};
		bool is_moving_down_{};
		bool is_moving_left_{};
		bool is_moving_right_{};
		sf::Texture texture_;
		sf::Sprite sprite_;
		float speed_ = 2.5;	// Default.
	};

}	// namespace fd

#endif ENTITY_H

