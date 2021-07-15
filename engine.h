#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
#include <thread>

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

	std::thread
		th_robot_move;

public:
	Engine();
	void start();
	
};

#endif // !ENGINE_H

