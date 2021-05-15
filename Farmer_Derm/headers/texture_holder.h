#ifndef TEXTURE_HOLDER_H
#define TEXTURE_HOLDER_H

#include <SFML/Graphics.hpp>
#include "headers/resource_identifiers.h"

namespace fd {
	class TextureHolder {
	public:
		sf::Texture& Get(fd::textures::ID id);
		const sf::Texture& Get(fd::textures::ID id) const;
		void Load(fd::textures::ID id, const std::string& filename);

	private:
		std::map <fd::textures::ID, std::unique_ptr<sf::Texture>> texture_map_;
	};
} // namespace fd
#endif

