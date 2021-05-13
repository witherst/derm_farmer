#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Graphics.hpp>
#include "headers/xml_parser.h"

namespace fd {
	class TileMap : public sf::Drawable, public sf::Transformable {
	public:
		TileMap() {}
		bool Load(const char* filename);
		XmlParser* GetMapParser() { return &map_parser_; }

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		sf::VertexArray vertices_;
		sf::Texture tileset_;
		XmlParser map_parser_;
	};
}
#endif

