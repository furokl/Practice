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
	//window.setFramerateLimit(60);

	std::vector<Item> item;
	item.push_back(Item(400.f, 330.f, Item_Type::TRASH, Item_Form::RECTANGLE));
	item.push_back(Item(350.f, 230.f, Item_Type::TRASH, Item_Form::RECTANGLE));
	item.push_back(Item(500.f, 350.f, Item_Type::TRASH, Item_Form::RECTANGLE));
	std::vector<Robot> robot;
	robot.push_back(Robot(200.f, 450.f));
	robot.push_back(Robot(700.f, 450.f));
	robot.push_back(Robot(400.f, 450.f));
	std::vector<Camera> camera;
	camera.push_back(Camera(450.f, 250.f));
	camera.push_back(Camera(500.f, 400.f));
	Item trash_can(700.f, 120.f, Item_Type::TRASH_CAN, Item_Form::RECTANGLE);

	for (size_t i{}; i < camera.size(); i++)
	{
		camera[i].set_item_points(item);
	}

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
		
		for (size_t i{}; i < robot.size(); i++)			// ROBOT
		{
			robot[i].draw_robot(window);
			robot[i].move(camera, item, trash_can);
			robot[i].play_sound();
		}
		

		for (size_t i{}; i < camera.size(); i++)		// CAMERA
		{
			camera[i].draw_camera(window);
			camera[i].draw_beam(window, item);
		}

		trash_can.draw_trash_can(window);				// ITEM
		
		for (size_t i{}; i < item.size(); i++)
		{
			item[i].draw_item(window);
		}

		window.draw(walls_sprite);
		window.display();
	}
}