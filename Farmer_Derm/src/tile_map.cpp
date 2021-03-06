#include "headers/tile_map.h"
#include <string>

namespace fd {

	bool TileMap::Load(const sf::Texture &tileset, const char* map_filename) {
		tileset_ = tileset;
		map_parser_.LoadMap(map_filename);

		const int map_height = map_parser_.GetMapWidth();
		const int map_width = map_parser_.GetMapHeight();	

		for (auto& cur_layer : map_parser_.GetLayers()) {
			// Populate collision set with tile numbers.
			if (cur_layer.layer_type == XmlParser::LayerType::kCollider) {
				for (unsigned int i = 0; i < map_width; i++) {
					for (unsigned int j = 0; j < map_height; j++) {
						if (cur_layer.tile_map[i + j * map_width] != "0") {
							collision_set.insert(MakeTileKey(i, j));
						}
					}
				}	
				continue;
			}
			sf::VertexArray	vertices;
			// Set primitive type and resize vertex array to fit our level size.
			vertices.setPrimitiveType(sf::Quads);
			// TODO: Possible overflow if you make a map that's the size of the universe.
			vertices.resize(map_height * map_width * 4);

			// Populate vertex array, with one quad per tile.
			for (unsigned int i = 0; i < map_width; i++) {
				for (unsigned int j = 0; j < map_height; j++) {
					// Get the tile number in our map that we will be mapping to.
					int cur_tile_number = stoi(cur_layer.tile_map[i + j * map_width]) - 1;
					// Empty tile.
					if (cur_tile_number < 0) { continue; }

					// Find the tile in the tilset texture map.	
					int tu = cur_tile_number % (tileset_.getSize().x / map_parser_.GetTileWidth());
					int tv = cur_tile_number / (tileset_.getSize().y / map_parser_.GetTileWidth());

					// Get pointer to current tile's quad.
					sf::Vertex* quad = &vertices[(i + j * map_width) * 4];

					// Define the quad's 4 corners.
					quad[0].position = sf::Vector2f(i * map_parser_.GetTileWidth(), j * map_parser_.GetTileHeight());
					quad[1].position = sf::Vector2f((i + 1) * map_parser_.GetTileWidth(), j * map_parser_.GetTileHeight());
					quad[2].position = sf::Vector2f((i + 1) * map_parser_.GetTileWidth(), (j + 1) * map_parser_.GetTileHeight());
					quad[3].position = sf::Vector2f(i * map_parser_.GetTileWidth(), (j + 1) * map_parser_.GetTileHeight());	

					// Define the quad's 4 texture coordinates.
					quad[0].texCoords = sf::Vector2f(tu * map_parser_.GetTileWidth(), tv * map_parser_.GetTileHeight());
					quad[1].texCoords = sf::Vector2f((tu + 1) * map_parser_.GetTileWidth(), tv * map_parser_.GetTileHeight());
					quad[2].texCoords = sf::Vector2f((tu + 1) * map_parser_.GetTileWidth(), (tv + 1) * map_parser_.GetTileHeight());
					quad[3].texCoords = sf::Vector2f(tu * map_parser_.GetTileWidth(), (tv + 1) * map_parser_.GetTileHeight());	
				}
			}
			layer_vertex_array_.push_back(vertices);
		}	

		return true;
	}

	std::string TileMap::MakeTileKey(int i, int j) const {
		return std::to_string(i) + ',' + std::to_string(j);
	}

	void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		// Apply the transform.
		states.transform *= getTransform();

		// Apply the tileset texture.
		states.texture = &tileset_;
		
		// Draw the layers
		for (auto& layer : layer_vertex_array_) {
			target.draw(layer, states);
		}
	}

}	// namespace fd

