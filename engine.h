#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>

class Engine
{
private:
	sf::RenderWindow window;

	sf::Texture background_texture;
	sf::Texture walls_texture;
	sf::Sprite background_sprite;
	sf::Sprite walls_sprite;

public:
	Engine();
	void start();
	
};

#endif // !ENGINE_H

