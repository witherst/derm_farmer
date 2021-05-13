// Built-in
#include <iostream>

// Game specific
#include "headers/game.h"
#include "headers/xml_parser.h"
#include "headers/tile_map.h"

// Third party

int main() {
	try {
		fd::Game game;
		game.Run();
		//fd::XmlParser map_xml("assets/art/tiled/map/farm_map.tmx");
		//map_xml.PrintLayerStatistics("ground");
		//map_xml.PrintObjectStatistics();
		//tmap.GetMapParser()->PrintLayerStatistics();
		
	}
	catch (std::exception& e) {
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}	

	// Chapter 3, p.50

	return 0; 
}

//	sf::RenderWindow window(sf::VideoMode(600, 600), "Test Game");
//	window.setFramerateLimit(60);
//	bool WINDOW_HAS_FOCUS = true;
//
//	sf::Texture sloppy_texture;
//	if (!sloppy_texture.loadFromFile("sloppy.png")) {
//		std::cout << "Error loading sloppy.png" << std::endl;
//		return 1;
//	}
//	sf::Sprite sloppy_sprite;
//	sloppy_sprite.setTexture(sloppy_texture);
//	sloppy_sprite.setOrigin(sloppy_sprite.getLocalBounds().width / 2., sloppy_sprite.getLocalBounds().height / 2.);
//	sloppy_sprite.setPosition(window.getSize().x / 2, window.getSize().y / 2);
//	sloppy_sprite.setScale({ .5, .5 });
//
//	sf::RectangleShape line(sf::Vector2f(150.f, 1.f));
//	line.setPosition(sloppy_sprite.getPosition().x, sloppy_sprite.getPosition().y);
//
//	while (window.isOpen()) {
//		window.clear(sf::Color::Black);		
//		sf::Event event;
//
//		while (window.pollEvent(event)) {
//			if (event.type == sf::Event::Closed) {
//				window.close();
//			}
//			if (event.type == sf::Event::Resized) {
//				sf::FloatRect visible_area(0, 0, event.size.width, event.size.height);
//				window.setView(sf::View(visible_area));	
//				sloppy_sprite.setPosition(window.getSize().x / 2, window.getSize().y / 2);
//			}
//			if (event.type == sf::Event::GainedFocus) {
//				WINDOW_HAS_FOCUS = true;
//			}
//			if (event.type == sf::Event::LostFocus){
//				WINDOW_HAS_FOCUS = false;
//			}
//
//		}
//
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
//			sloppy_sprite.move(1., 0.);
//			line.move(1., 0.);
//			if (sloppy_sprite.getPosition().x >= window.getSize().x) {
//				sloppy_sprite.setPosition(0, sloppy_sprite.getPosition().y);
//				line.setPosition(0, line.getPosition().y);
//			}
//			if (sloppy_sprite.getPosition().y >= window.getSize().y) {
//				sloppy_sprite.setPosition(sloppy_sprite.getPosition().x, 0);
//				line.setPosition(line.getPosition().x, 0);
//			}
//		}
//
//		if (WINDOW_HAS_FOCUS && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
//			sloppy_sprite.rotate(1.);
//			line.rotate(1.);
//		}
//
//		if (WINDOW_HAS_FOCUS && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
//			Eigen::Vector2d sloppy_center(sloppy_sprite.getPosition().x, sloppy_sprite.getPosition().y);
//			Eigen::Vector2d mouse_point(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y );
//
//			Eigen::Vector2d mouse_line_vector = mouse_point - sloppy_center;
//			Eigen::Vector2d sloppy_line = Eigen::Vector2d(sloppy_center.x() + 150.0, sloppy_center.x()) - sloppy_center;
//			//Eigen::Vector2d sloppy_line = Eigen::Vector2d(line.getPoint[1].x, line.getPoint[1].y);
//
//			sf::Vertex draw_mouse_line[] = {
//				sf::Vertex(sf::Vector2f(sloppy_center.x(), sloppy_center.y())),
//				sf::Vertex(sf::Vector2f(mouse_point.x(), mouse_point.y())),
//			};
//
//			float cross = mouse_line_vector.y() * sloppy_line.x() - mouse_line_vector.x() * sloppy_line.y();
//			float degree = atan2(abs(cross), mouse_line_vector.dot(sloppy_line)) * 180 / EIGEN_PI;	
//			degree = (cross < 0) ? 360 - degree : degree;	
//			std::cout << degree << std::endl;
//
//			sloppy_sprite.setRotation(degree);
//			line.setRotation(degree);
//			
//			window.draw(draw_mouse_line, 2, sf::Lines);
//		}
//
//		window.draw(sloppy_sprite);
//		window.draw(line);
//		window.display();
//	}
