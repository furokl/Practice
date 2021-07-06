#ifndef ITEM_H
#define ITEM_H

#include <vector>
#include <SFML/Graphics.hpp>

class Item
{
private:
	float
		x, y,
		x_stretch, y_stretch;

	struct Polygon 
	{
		std::vector<float> point;
	};

	Item_Type type;
	Item_Form form;
	
	sf::Texture item_texture;
	sf::Texture trash_can_texture;
	sf::Sprite item_sprite;
	sf::Sprite trash_can_sprite;

public:
	Polygon polygon;
	Item(float, float, Item_Type, Item_Form);
	void get_coord(float&, float&);
	bool get_item_type();
	void make_volume(Item_Form form);

	// SFML

	void draw_item(sf::RenderWindow&);
	void draw_trash_can(sf::RenderWindow&);
};

#endif // !ITEM_H