#include "engine.h"

Engine::Engine()
{
	background_texture.loadFromFile("D:\\FuroK\\Visual Studio\\Texture\\Practice\\room.png");
	background_sprite.setTexture(background_texture);
}

void Engine::start() {
	sf::RenderWindow window(sf::VideoMode(1100, 600), "RoboTrash");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color::White);
		window.draw(background_sprite);
		window.display();
	}
}