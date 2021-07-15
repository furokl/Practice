#include <iostream>
#include <thread>
#include <Windows.h>
// for <Windows.h>
#undef min
#undef max

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
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	sf::RenderWindow window(sf::VideoMode(1100, 600), "RoboTrash");
	window.setFramerateLimit(60);

	std::vector<Item> item{
	Item(400.f, 330.f, Item_Type::TRASH, Item_Form::RECTANGLE),
	Item(500.f, 230.f, Item_Type::TRASH, Item_Form::RECTANGLE),
	Item(540.f, 400.f, Item_Type::TRASH, Item_Form::RECTANGLE)
	};
	std::vector<Robot> robot{
	Robot(200.f, 450.f),
	Robot(700.f, 450.f),
	Robot(400.f, 450.f)
	};
	std::vector<Camera> camera{
	Camera(450.f, 250.f),
	Camera(500.f, 400.f)
	};
	for (size_t i{}; i < camera.size(); i++)
	{
		camera[i].set_item_points(item);
	}
	Item trash_can(700.f, 120.f, Item_Type::TRASH_CAN, Item_Form::RECTANGLE);

	sf::Clock clock = sf::Clock::Clock();
	sf::Time previous_time = clock.getElapsedTime();
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
		// BEGIN
		window.clear(sf::Color(225,225,225));
		window.draw(background_sprite);
		
		// ROBOT
		for (auto &robot_ : robot)
		{
			robot_.draw_robot(window);
			std::thread th_robot_move([&] {
				robot_.move(camera, item, trash_can);
				robot_.play_sound();
				});
			th_robot_move.detach();
		}
		
		// CAMERA
		for (auto &camera_ : camera)
		{
			camera_.draw_camera(window);
			camera_.draw_beam(window, item);
		}

		// ITEMS
		trash_can.draw_trash_can(window);
		for (auto &item_ : item)
		{
			item_.draw_item(window);
		}

		// END
		window.draw(walls_sprite);
		window.display();

		// FPS
		current_time = clock.getElapsedTime();	
		fps = 1.f / (current_time.asSeconds() - previous_time.asSeconds());
		if (fps < 30.f) 
			SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | Red));
		else if ((30.f < fps) && (fps < 60.f))
			SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | Yellow));
		else if (fps > 60.f)
			SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | LightGreen));
		std::cout << "\t*\t" << floor(fps) << "\t*" << std::endl;
		previous_time = current_time;
	}
}