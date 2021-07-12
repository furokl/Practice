#include <iostream>
#include <thread>

#include "admin.h"
#include "robot.h"
#include "camera.h"
#include "item.h"

#include "engine.h"

Engine::Engine()
{
	background_texture.loadFromFile("C:\\Users\\User\\source\\repos\\RoboTrash_SFML\\redist\\room.png");
	background_sprite.setTexture(background_texture);

	walls_texture.loadFromFile("C:\\Users\\User\\source\\repos\\RoboTrash_SFML\\redist\\walls.png");
	walls_sprite.setTexture(walls_texture);
}

void Engine::start() {
	sf::RenderWindow window(sf::VideoMode(1100, 600), "RoboTrash");

	std::vector<Item> item;
	item.push_back(Item(400.f, 330.f, Item_Type::TRASH, Item_Form::RECTANGLE));
	item.push_back(Item(350.f, 230.f, Item_Type::TRASH, Item_Form::RECTANGLE));
	item.push_back(Item(500.f, 350.f, Item_Type::TRASH, Item_Form::RECTANGLE));

	Item trash_can(700.f, 120.f, Item_Type::TRASH_CAN, Item_Form::RECTANGLE);
	/*
	std::vector<Robot> robot;
	robot.push_back(Robot(200.f, 450.f));
	robot.push_back(Robot(700.f, 450.f));
	robot.push_back(Robot(400.f, 450.f));
	*/
	Robot robot(200.f, 450.f);

	Camera camera(450.f, 250.f);


	camera.set_item_points(item);

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
		
		robot.draw_robot(window);
		std::thread th_robot_move([&] {
			robot.move(camera, item, trash_can);
			robot.play_sound();
			});
		th_robot_move.detach();
		/*
		for (size_t i{}; i < robot.size(); i++)
		{
			robot[i].draw_robot(window);
			robot[i].move(camera, item, trash_can);
			robot[i].play_sound();
		}
		*/

		camera.draw_camera(window);
		camera.draw_beam(window, item);

		trash_can.draw_trash_can(window);
		for (size_t i{}; i < item.size(); i++)
		{
			item[i].draw_item(window);
		}

		window.draw(walls_sprite);
		window.display();
	}
}