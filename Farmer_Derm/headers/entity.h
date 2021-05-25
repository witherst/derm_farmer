#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

namespace fd {

	class Entity {
	public:
		void SetTexture(sf::Texture& texture);
		const sf::Texture& GetTexture() const { return texture_; };

	private:
		sf::Texture texture_;
	};

}	// namespace fd

#endif ENTITY_H

