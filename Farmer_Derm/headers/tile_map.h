#ifndef TILEMAP_H
#define TILEMAP_H

#include <string>
#include <unordered_set>

#include <SFML/Graphics.hpp>
#include "headers/xml_parser.h"

namespace fd {
	
	/*
		TileMap creates a vertex array with u,v coordinates that correspond to the tile created in the program Tiled.
		This information comes from the XmlParser.
	*/
	class TileMap : public sf::Drawable, public sf::Transformable {
	public:
		TileMap() {}
		bool Load(const sf::Texture &tileset, const char* map_filename);
		std::string MakeTileKey(int i, int j) const;
		const std::unordered_set<std::string>* GetCollisionSet() const { return &collision_set; }
		XmlParser* GetMapParser() { return &map_parser_; }
		

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		sf::Texture tileset_;
		std::unordered_set<std::string> collision_set;
		std::vector<sf::VertexArray> layer_vertex_array_;
		XmlParser map_parser_;	
	};

}	// namespace fd
#endif

