#ifndef XML_PARSER_H
#define XML_PARSER_H

#include <iostream>
#include <string>
#include <vector>
#include "third_party/pugixml-1.11/src/pugixml.hpp"

namespace fd {
	class XmlParser {
	public:	
		XmlParser() {};
		XmlParser(const char* filename)
			//: result(doc.load_file(file_name))
		{
			LoadMap(filename);
		}

		// To print out this enum outside of this class:
		//	std::cout << static_cast<std::underlying_type<XmlParser::LayerType>::type>(cur_layer.layer_type) << std::endl;
		enum class LayerType {
			kRenderTiles,
			kCollider,
			kInvisible,
		};

		struct layer_info {
			LayerType layer_type = LayerType::kRenderTiles;
			float width = 0.;
			float height = 0.;
			float pos_x = -1.;
			float pos_y = -1.;
			int id = 0;
			std::string name = "";	
			std::vector<std::string> tile_map;
		};

		struct object_group_info {
			std::string object_group_name = "";
			int object_group_id = 0;
			std::vector<layer_info> object_info;
		};

		const int GetMapNumTilesInX()								{ return num_tiles_x; }
		const int GetMapNumTilesInY()								{ return num_tiles_y; }
		const int GetMapHeightInPixels()							{ return GetMapNumTilesInY() * GetTileHeightInPixels(); }
		const int GetMapWidthInPixels()								{ return GetMapNumTilesInX() * GetTileWidthInPixels(); }
		const int GetTileWidthInPixels()							{ return tile_width; }
		const int GetTileHeightInPixels()							{ return tile_height; }
		const int GetFirstGid()										{ return firstgid; }
		const std::string GetTileSource()							{ return tile_source; }
		const std::vector<layer_info> GetLayers()					{ return layers; }
		const std::vector<object_group_info> GetObjects()			{ return objects; }
		void LoadMap(const char* filename);	
		void PrintLayerStatistics(std::string print_name = "");
		void PrintObjectStatistics(std::string print_name = "");

	private:
		void PopulateLayers();
		void PopulateMapAttrs();
		void PopulateObjects();	

		int firstgid = 0;
		int map_width_in_pixels = 0;
		int map_height_in_pixels = 0;
		int num_tiles_x = 0;
		int num_tiles_y = 0;
		int tile_width = 0;
		int tile_height = 0;
		std::string tile_source = "";
		std::vector<layer_info> layers;
		std::vector<object_group_info> objects;

		pugi::xml_document doc;
		pugi::xml_parse_result result;	
	};
} // namespace fd

#endif

