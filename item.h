#ifndef ITEM_H
#define ITEM_H

#include <vector>
#include <SFML/Graphics.hpp>

class Item
{
private:
	std::string
		file_path{ "C:\\Users\\������\\source\\repos\\RoboTrash_SFML\\redist\\" },
		file_name;
	float
		x, 
		y,
		x_stretch, 
		y_stretch;

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
	float get_coord_x();
	float get_coord_y();
	Item_Type get_item_type();
	void set_coord(float&, float&);
	void set_item_type();
	void make_volume(Item_Form form);

	// SFML

	void draw_item(sf::RenderWindow&);
	void draw_trash_can(sf::RenderWindow&);
};

#endif // !ITEM_H