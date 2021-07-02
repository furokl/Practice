#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>

#include "robot.h"
#include "camera.h"
#include "item.h"

class Engine
{
private:
	sf::RenderWindow window;

	sf::Texture background_texture;
	sf::Sprite background_sprite;

	//Robot robot(double, double);
	//Camera camera(double, double);
	//Item item(double, double, Item_Type, Item_Form);

public:
	Engine();
	void start();

	
};

#endif // !ENGINE_H

