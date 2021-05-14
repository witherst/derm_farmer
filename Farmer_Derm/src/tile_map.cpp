#include "headers/tile_map.h"
#include <string>

namespace fd {

	bool TileMap::Load(const char* texture_filename, const char* map_filename) {
		// Load map texture file.
		if (!tileset_.loadFromFile(texture_filename)) {
			return false;
		}
		// Load map with our map parser.
		map_parser_.LoadMap(map_filename);

		const int map_height = map_parser_.GetMapWidth();
		const int map_width = map_parser_.GetMapHeight();

		// Set primitive type and resize vertex array to fit our level size.
		vertices_.setPrimitiveType(sf::Quads);
		// TODO: Possible overflow if you make a map that's the size of the universe.
		vertices_.resize(map_height * map_width * 4);

		// Populate vertex array, with one quad per tile.
		for (unsigned int i = 0; i < map_width; i++) {
			for (unsigned int j = 0; j < map_height; j++) {
				// Get the tile number in our map that we will be mapping to.
				std::cout << map_parser_.GetLayers()[1].tile_map[i][j] << " ";
				int cur_tile_number = stoi(map_parser_.GetLayers()[1].tile_map[i][j]);

				// Find the tile in the tilset texture map.	
				int tu = cur_tile_number % (tileset_.getSize().x / map_parser_.GetTileWidth());
				int tv = cur_tile_number / (tileset_.getSize().y / map_parser_.GetTileWidth());

				// Get pointer ot current tile's quad.
				sf::Vertex* quad = &vertices_[(i + j * map_width) * 4];

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
			std::cout << '\n';
		}

		return true;
	}

	void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		// Apply the transform.
		states.transform *= getTransform();

		// Apply the tileset texture.
		states.texture = &tileset_;

		target.draw(vertices_, states);
	}

}	// namespace fd

