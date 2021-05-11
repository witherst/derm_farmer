#include "headers/xml_parser.h"

namespace fd {
	void XmlParser::LoadMap(const char* filename) {
		result = doc.load_file(filename);
		if (!result) {
			std::cout << "ERROR Loading file: " << filename << std::endl;
			std::cout << "ERROR: " << result.description() << std::endl;
			return;
		}

		PopulateMapAttrs();
		PopulateLayers();
	}
	void XmlParser::PopulateMapAttrs() {
		map_width = doc.child("map").attribute("width").as_int();
		map_height = doc.child("map").attribute("height").as_int();
		tile_width = doc.child("map").attribute("tilewidth").as_int();
		tile_height = doc.child("map").attribute("tileheight").as_int();
		tile_source = doc.child("map").child("tileset").attribute("source").as_string();
		firstgid = doc.child("map").child("tileset").attribute("firstgid").as_int();
	}

	/* 
		Note: Rotated tiles in Tiled are stored as unsigned long int (10 chars) -- 8 bytes
		A string stores 1 byte per character. Unsigned long int string == 10 bytes. It's much
		more space effective to store each tile id as a string. Talking 7440 bytes versus 1000 in some
		cases.
		** Only notable exception of storing the tile as a string is if a GREAT majority of tiles are rotated
		   in tiled, which I doubt will be the case.
	*/
	void XmlParser::PopulateLayers() {	
		for (pugi::xml_node tool = doc.child("map").child("layer"); tool; tool = tool.next_sibling("layer")) {
			layer_info cur_layer;
			cur_layer.name = tool.attribute("name").as_string();
			cur_layer.id = tool.attribute("id").as_int();
			cur_layer.layer_height = tool.attribute("height").as_int();
			cur_layer.layer_width = tool.attribute("width").as_int();

			std::string data = tool.child("data").child_value();
			std::string characters = "";	
			std::vector<std::string> row;
			for (auto& ch : data) {
				if (ch == ',' || ch == '\n') { 
					row.push_back(characters);
					characters = "";
					if (ch == '\n') {
						cur_layer.tile_map.push_back(row);
						row.clear();
					}
					continue;
				}
				characters += ch;
			}
			
			layers.push_back(cur_layer);
		}
	}
	void XmlParser::PrintStatistics(std::string print_name) {
		std::cout << "\n************Map Stats************\n";
		std::cout << "Map width:\t" << map_width << " tiles\tMap height:\t" << map_height << " tiles\n";
		std::cout << "Tile width:\t" << tile_width << "px\t\tTile height:\t" << tile_height << "px\n";
		std::cout << "Tile source:\t" << tile_source << "\tFirstgid:\t" << firstgid << "\n";

		std::cout << "\n*****LAYERS:\n";
		for (auto& layer : layers) {
			std::cout << "Layer:\t" << layer.name << "\tID: " << layer.id << 
				"\tWidth:\t" << layer.layer_width << " tiles\t" << "Height:\t" <<
				layer.layer_height << " tiles\n";
			
			if (print_name == "" || layer.name == print_name) {
				for (int i = 0; i < layer.tile_map.size(); i++) {
					for (int j = 0; j < layer.tile_map[i].size(); j++) {
						if (j % layer.layer_width == 0) {
							std::cout << '\n';
						}
						std::cout << layer.tile_map[i][j] << " ";
					}
				}
				std::cout << "\n\n";
			}	
		}	
	}
}; // namespace fd
