#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Graphics.hpp>
#include "headers/xml_parser.h"

namespace fd {

	class TileMap : public sf::Drawable, public sf::Transformable {
	public:
		TileMap() {}
		bool Load(const sf::Texture &tileset, const char* map_filename);
		XmlParser* GetMapParser() { return &map_parser_; }

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		std::vector<sf::VertexArray> layer_vertices_;
		sf::Texture tileset_;
		XmlParser map_parser_;
	};

}	// namespace fd
#endif

