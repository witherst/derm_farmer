#ifndef TEXTURE_HOLDER_H
#define TEXTURE_HOLDER_H

#include <SFML/Graphics.hpp>
#include "headers/resource_identifiers.h"

class TextureHolder {
public:	
	sf::Texture& Get(Textures::ID id);
	const sf::Texture& Get(Textures::ID id) const;
	void Load(Textures::ID id, const std::string& filename);

private:
	std::map <Textures::ID, std::unique_ptr<sf::Texture>> texture_map_;
};
#endif

