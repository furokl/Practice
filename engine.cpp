#include "engine.h"
#include "robot.h"
#include "camera.h"
#include "item.h"

Engine::Engine()
{
	background_texture.loadFromFile("D:\\FuroK\\Visual Studio\\Texture\\Practice\\room.png");
	background_sprite.setTexture(background_texture);
}

void Engine::start() {
	sf::RenderWindow window(sf::VideoMode(1100, 600), "RoboTrash");


	Item trash(200.0, 200.0, Item_Type::TRASH, Item_Form::RECTANGLE);
	Robot robot(0.0, 0.0);
	Camera camera(150.0, 150.0);

	camera.set_item_points(trash);
	camera.make_beam(trash);
	//robot.move(camera);
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

		trash.draw_item(window);
		robot.draw_robot(window);
		camera.draw_camera(window);
		camera.draw_beam(window, trash);

		window.display();
	}
}