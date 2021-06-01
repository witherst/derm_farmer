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
		PopulateObjects();
	}
	void XmlParser::PopulateMapAttrs() {
		num_tiles_x = doc.child("map").attribute("width").as_int();
		num_tiles_y = doc.child("map").attribute("height").as_int();
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
			cur_layer.height = tool.attribute("height").as_float();
			cur_layer.width = tool.attribute("width").as_float();		
			
			// Get custom properties.
			for (pugi::xml_node property_tool = tool.child("properties").child("property"); property_tool; property_tool = property_tool.next_sibling("property")) {
				std::string name_of_property = property_tool.attribute("name").as_string();
				if (name_of_property == "isCollision") {
					cur_layer.layer_type = LayerType::kCollider;
				}
			}

			std::string data = tool.child("data").child_value();
			std::string characters = "";	
			int count = 0;
			for (auto& ch : data) {
				if (ch >= 48 && ch <= 57) {
					characters += ch;
				}
				else if (ch == ',' && characters.length() > 0) {
					cur_layer.tile_map.push_back(characters);
					characters = "";
				}
				else if (ch == '\n' && characters.length() > 0) { 
					// Need this check for the very last character in the map.
					cur_layer.tile_map.push_back(characters);
					characters = "";
				}
			}
			
			layers.push_back(cur_layer);
		}
	}

	void XmlParser::PopulateObjects() {
		for (pugi::xml_node tool = doc.child("map").child("objectgroup"); tool; tool = tool.next_sibling("objectgroup")) {
			object_group_info cur_obj_group;
			cur_obj_group.object_group_name = tool.attribute("name").as_string();
			cur_obj_group.object_group_id = tool.attribute("id").as_int();

			for (pugi::xml_node obj_tool = tool.child("object"); obj_tool; obj_tool = obj_tool.next_sibling("object")) {	
				layer_info object_info;
				object_info.name = obj_tool.attribute("name").as_string();
				object_info.id = obj_tool.attribute("id").as_int();
				object_info.height = obj_tool.attribute("height").as_float();
				object_info.width = obj_tool.attribute("width").as_float();
				object_info.pos_x = obj_tool.attribute("x").as_float();
				object_info.pos_y = obj_tool.attribute("y").as_float();
				cur_obj_group.object_info.push_back(object_info);
			}
			
			objects.push_back(cur_obj_group);
		}
	}

	void XmlParser::PrintLayerStatistics(std::string print_name) {
		std::cout << "\n************Map Stats************\n";
		std::cout << "Number of map tiles in x:\t" << num_tiles_x << " tiles\tNumber of map tiles in y: \t" << num_tiles_y << " tiles\n";
		std::cout << "Tile width:\t" << tile_width << "px\t\tTile height:\t" << tile_height << "px\n";
		std::cout << "Tile source:\t" << tile_source << "\tFirstgid:\t" << firstgid << "\n";

		std::cout << "\n*****LAYERS:\n";
		for (auto& layer : layers) {
			std::cout << "Layer:\t" << layer.name << "\tID: " << layer.id << 
				"\tWidth:\t" << layer.width << " tiles\t" << "Height:\t" <<
				layer.height << " tiles\n";
			
			if (print_name == "" || layer.name == print_name) {
				for (int i = 0; i < layer.tile_map.size(); i++) {
					std::cout << layer.tile_map[i] << " ";
					if ((i+1) % num_tiles_x == 0) {
						std::cout << '\n';
					}
				}
				std::cout << "\n\n";
			}	
		}	
	}
	
	void XmlParser::PrintObjectStatistics(std::string print_name) {
		std::cout << "\n*****OBJECTS*****\n";
		for (auto& object_grp : objects) {
			if (print_name == "" || object_grp.object_group_name == print_name) {
				std::cout << "Group Name: " << object_grp.object_group_name << " -- ID: " << object_grp.object_group_id << "\n";

				for (auto& object : object_grp.object_info) {
					std::cout << "\tName:\t" << object.name << "\tID: " << object.id << "\n";
					std::cout << "\tWidth:\t" << object.width << " pixels\tHeight:\t" << object.height << " pixels\n";
					std::cout << "\tPos: \t(" << object.pos_x << ", " << object.pos_y << ")\n";	
					std::cout << "\n";
				}	
			}
		}	
	}

}; // namespace fd
