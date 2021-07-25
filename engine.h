#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
#include <thread>

#include "robot.h"
#include "camera.h"

class Engine
{
private:
	std::string
		file_path{ "C:\\Users\\Даниил\\source\\repos\\RoboTrash_SFML\\redist\\" },
		file_name;
	float
		fps;

	sf::RenderWindow window;

	sf::Texture background_texture;
	sf::Texture walls_texture;
	sf::Sprite background_sprite;
	sf::Sprite walls_sprite;

	sf::Clock clock;
	sf::Time previous_time;
	sf::Time current_time;

	sf::Vector2i mouse;

	std::thread th_robot_move;
	std::thread th_camera;

public:
	Engine();
	~Engine();
	void start();

};

#endif // !ENGINE_H

