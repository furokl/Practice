#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
#include <thread>

#include "robot.h"
#include "camera.h"

class Engine
{
private:
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
	void click(std::vector<Camera>&, std::vector<Robot>&);
};

#endif // !ENGINE_H

