#include <iostream>

#include "admin.h"
#include "robot.h"
#include "camera.h"
#include "item.h"

#include "engine.h"

Engine::Engine()
{
	background_texture.loadFromFile("D:\\FuroK\\Visual Studio\\Texture\\Practice\\room.png");
	background_sprite.setTexture(background_texture);

	walls_texture.loadFromFile("D:\\FuroK\\Visual Studio\\Texture\\Practice\\walls.png");
	walls_sprite.setTexture(walls_texture);
}

void Engine::start() {
	sf::RenderWindow window(sf::VideoMode(1100, 600), "RoboTrash");

	Item trash_can(700.f, 120.f, Item_Type::TRASH_CAN, Item_Form::RECTANGLE);
	Item trash(140.f, 280.f, Item_Type::TRASH, Item_Form::RECTANGLE);
	Robot robot(700.f, 450.f);
	Camera camera(250.f, 250.f);

	camera.set_item_points(trash);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
			}
		}
		window.clear(sf::Color(225,225,225));

		window.draw(background_sprite);

		trash_can.draw_trash_can(window);
		trash.draw_item(window);
		robot.draw_robot(window);
		robot.move(camera);
		camera.draw_camera(window);
		camera.draw_beam(window, trash);

		window.draw(walls_sprite);

		window.display();
	}
}