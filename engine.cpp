#include <iostream>
#include <thread>
#include <Windows.h>
// for <Windows.h>
#undef min
#undef max

#include "admin.h"
#include "item.h"

#include "engine.h"

Engine::Engine()
{
	file_name = "room.png";
	background_texture.loadFromFile(file_path + file_name);
	if (!background_texture.loadFromFile(file_path + file_name))
	{
		std::cout << "\n!!!\tloadFromFile(" << file_name << ')' << std::endl;
		std::exit(EXIT_FAILURE);
	}
	background_sprite.setTexture(background_texture);

	walls_texture.loadFromFile("C:\\Users\\Даниил\\source\\repos\\RoboTrash_SFML\\redist\\walls.png");
	walls_sprite.setTexture(walls_texture);
}

Engine::~Engine()
{
}

void Engine::start() {

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	sf::Clock clock = sf::Clock::Clock();
	sf::Time previous_time = clock.getElapsedTime();

	sf::RenderWindow window(sf::VideoMode(1100, 600), "RoboTrash");
	window.setFramerateLimit(60);

	std::vector<Item> item{
	Item(400.f, 330.f, Item_Type::TRASH, Item_Form::RECTANGLE),
	Item(500.f, 230.f, Item_Type::TRASH, Item_Form::RECTANGLE),
	Item(540.f, 400.f, Item_Type::TRASH, Item_Form::RECTANGLE),
	Item(345.f, 400.f, Item_Type::TRASH, Item_Form::RECTANGLE)
	};
	Item trash_can(700.f, 120.f, Item_Type::TRASH_CAN, Item_Form::RECTANGLE);

	std::vector<Robot> robot{
		Robot(200.f, 450.f),
		Robot(700.f, 450.f),
		Robot(400.f, 450.f)
	};

	std::vector<Camera> camera{
		Camera(450.f, 250.f),
		Camera(500.f, 400.f),
		Camera(400.f, 100.f)
	};
	for (size_t i{}; i < camera.size(); i++)
	{
		camera[i].set_item_points(item);
	}

	Admin admin(robot, camera);
	admin.set_camera_on();
	admin.set_robot_on();
	admin.set_camera_off(0);
	admin.set_robot_off(0);

	// thread
	for (auto& robot_ : robot)
	{
		th_robot_move = std::thread([&] {
			robot_.move(camera, item, trash_can);
			});
		th_robot_move.detach();
	}
	for (auto& camera_ : camera)
	{
		th_camera = std::thread([&] {
			camera_.make_beam(item);
			});
		th_camera.detach();
	}
	for (auto& camera_ : camera)
	{
		th_camera = std::thread([&] {
			camera_.rotate();
			});
		th_camera.detach();
	}

	while (window.isOpen())
	{

		sf::Vector2i mouse = sf::Mouse::getPosition(window);
		sf::Event event;

		while (window.pollEvent(event))
		{
			// WINDOW
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::LostFocus)
				std::getchar();

			// MOUSE
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
			{
				for (size_t i{}; i < camera.size(); i++)
				{
					if (((camera[i].get_coord_x() - 10.f < mouse.x) 
							&& (mouse.x < camera[i].get_coord_x() + 10.f))
						&& ((camera[i].get_coord_y() - 10.f < mouse.y) 
							&& (mouse.y < camera[i].get_coord_y() + 10.f)))
					{
						admin.set_camera_on(i);
					}
				}
				for (size_t i{}; i < robot.size(); i++)
				{
					if (((robot[i].get_coord_x() - 25.f < mouse.x)
							&& (mouse.x < robot[i].get_coord_x() + 25.f))
						&& ((robot[i].get_coord_y() - 25.f < mouse.y)
							&& (mouse.y < robot[i].get_coord_y() + 25.f)))
					{
						admin.set_robot_on(i);
					}
				}
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				for (size_t i{}; i < camera.size(); i++)
				{
					if (((camera[i].get_coord_x() - 10.f < mouse.x)
							&& (mouse.x < camera[i].get_coord_x() + 10.f))
						&& ((camera[i].get_coord_y() - 10.f < mouse.y)
							&& (mouse.y < camera[i].get_coord_y() + 10.f)))
					{
						admin.set_camera_off(i);
					}
				}
				for (size_t i{}; i < robot.size(); i++)
				{
					if (((robot[i].get_coord_x() - 25.f < mouse.x)
						&& (mouse.x < robot[i].get_coord_x() + 25.f))
						&& ((robot[i].get_coord_y() - 25.f < mouse.y)
							&& (mouse.y < robot[i].get_coord_y() + 25.f)))
					{
						admin.set_robot_off(i);
					}
				}
			}
		}
		// BEGIN
		window.clear(sf::Color(225,225,225));
		window.draw(background_sprite);

		// ROBOT
		for (size_t i{}; i < robot.size(); i++)
		{
			if (admin.get_robot_power(i))
			{
				robot[i].set_thread_flag(true);
			}
			robot[i].draw_robot(window);
			robot[i].set_thread_flag(false);
		}

		// CAMERA
		for (size_t i{}; i < camera.size(); i++)
		{
			if (admin.get_camera_power(i))
			{
				camera[i].set_thread_flag(true);
				camera[i].draw_beam(window, item);
			}
			camera[i].draw_camera(window);
			camera[i].set_thread_flag(false);
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
