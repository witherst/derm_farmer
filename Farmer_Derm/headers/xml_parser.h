#ifndef XML_PARSER_H
#define XML_PARSER_H

#include <iostream>
#include <string>
#include <vector>
#include "third_party/pugixml-1.11/src/pugixml.hpp"

namespace fd {
	class XmlParser {
	public:	
		XmlParser(const char* filename)
			//: result(doc.load_file(file_name))
		{
			LoadMap(filename);
		}

		struct layer_info {
			std::string name = "";
			int id = 0;
			int layer_width = 0;
			int layer_height = 0;
			std::vector<std::vector<std::string>> tile_map;
		};

		const int GetMapWidth()						{ return map_width; }
		const int GetMapHeight()					{ return map_height; }
		const int GetTileWidth()					{ return tile_width; }
		const int GetTileHeight()					{ return tile_height; }
		const int GetFirstGid()						{ return firstgid; }
		const std::string GetTileSource()		{ return tile_source; }
		const std::vector<layer_info> GetLayers()	{ return layers; }
		void LoadMap(const char* filename);	
		void PrintStatistics(std::string print_name = "");

	private:
		void PopulateMapAttrs();
		void PopulateLayers();	

		int firstgid = 0;
		int map_width = 0;
		int map_height = 0;
		int tile_width = 0;
		int tile_height = 0;
		std::string tile_source = "";
		std::vector<layer_info> layers;

		pugi::xml_document doc;
		pugi::xml_parse_result result;	
	};
} // namespace fd

#endif

