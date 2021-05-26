#include "headers/entity.h"

namespace fd {

	void Entity::SetTexture(sf::Texture& texture) {
		texture_ = texture;
	}

	void Entity::SetSpriteTexture(sf::Texture& texture) {
		sprite_.setTexture(texture);
	}
/*
		player_.setPosition(view_.getSize().x / 2., view_.getSize().y / 2.);
*/

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

