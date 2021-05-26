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
		void SetTexture(sf::Texture& texture);	
		void SetSpriteTexture(sf::Texture& texture);
		void SetupEntity(ResourceHolder<sf::Texture, textures::ID>& resource_holder, sf::View& view);
		void SetInitialTransforms(sf::View& view);

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		sf::Texture texture_;
		sf::Sprite sprite_;
	};

}	// namespace fd

#endif ENTITY_H

