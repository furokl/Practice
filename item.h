#ifndef ITEM_H
#define ITEM_H

#include <vector>
#include <SFML/Graphics.hpp>

class Item
{
private:
	double x, y, x_stretch{ 20.0 }, y_stretch{ 20.0 };
	struct Polygon 
	{
		std::vector<double> point;
	};
	Item_Type type;
	Item_Form form;
	
	sf::Texture item_texture;
	sf::Sprite item_sprite;

public:
	Polygon polygon;
	Item(double, double, Item_Type, Item_Form);
	void get_coord(double&, double&);
	bool get_item_type();
	void make_volume(Item_Form form);
	void set_scale(double&, double&);

	// SFML

	void draw_item(sf::RenderWindow&);
};

#endif // !ITEM_H