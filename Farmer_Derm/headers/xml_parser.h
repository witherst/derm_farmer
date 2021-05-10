#ifndef XML_PARSER_H
#define XML_PARSER_H

#include <iostream>
#include <string.h>
#include "third_party/pugixml-1.11/src/pugixml.hpp"

namespace fd {
	class XmlParser {
	public:
		XmlParser(const char* file_name)
			: result(doc.load_file(file_name))
		{
			std::cout << "Load result: " << result.description() << "\n";	
			// Note: Rotated tiles in Tiled are stored as unsigned long int (10 chars) -- 8 bytes
			//	A string stores 1 byte per character. Unsigned long int string == 10 bytes. It's much
			//	more space effective to store each tile id as a string. Talking 7440 bytes versus 1000 in some
			//	cases.
			// ** Only notable exception of storing the tile as a string is if a GREAT majority of tiles are rotated
			//		in tiled, which I doubt will be the case.
			for (pugi::xml_node tool = doc.child("map").child("layer"); tool; tool = tool.next_sibling("layer")) {
				std::string name = tool.attribute("name").value();	
				std::cout << "Layer: " << name << "\n";
				if (name == "ground") {
					std::string data = tool.child("data").child_value();
					std::string temp = "";	
					for (auto& ch : data) {
						if (ch == ',' || ch == '\n') { 
							// Do something with temp, add to vector, etc...
							temp = "";
							continue;
						}
						temp += ch;
					}
				}
			}

		}

	private:
		pugi::xml_document doc;
		pugi::xml_parse_result result;
	};
} // namespace fd

#endif

