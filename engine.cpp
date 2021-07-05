#include "engine.h"
#include "robot.h"
#include "camera.h"
#include "item.h"
#include "control_system.h"

Engine::Engine()
{
	background_texture.loadFromFile("D:\\FuroK\\Visual Studio\\Texture\\Practice\\room.png");
	background_sprite.setTexture(background_texture);
}

void Engine::start() {
	sf::RenderWindow window(sf::VideoMode(1100, 600), "RoboTrash");

	Item trash_can(700, 120, Item_Type::TRASH_CAN, Item_Form::CIRCLE);
	Item trash(140.0, 280.0, Item_Type::TRASH, Item_Form::CIRCLE);
	Robot robot(0.0, 0.0);
	Camera camera(250.0, 250.0);

	camera.set_item_points(trash);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color(225,225,225));
		window.draw(background_sprite);

		trash_can.draw_trash_can(window);
		trash.draw_item(window);
		robot.draw_robot(window);
		robot.move(camera);
		camera.draw_camera(window);
		camera.draw_beam(window, trash);

		window.display();
	}
}