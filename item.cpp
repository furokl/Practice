#include <iostream>

#include "enum_states.h"
#include "item.h"


Item::Item(double x_, double y_, Item_Type type_, Item_Form form_)
	: x(x_), y(y_), type(type_), form(form_)
{
	make_volume(form_);

	item_texture.loadFromFile("D:\\FuroK\\Visual Studio\\Texture\\Practice\\item.png");
	item_sprite.setTexture(item_texture);
}

void Item::get_coord(double& temp_x, double& temp_y) {
	temp_x = x;
	temp_y = y;
}

bool Item::get_item_type() {
	switch (type)
	{
	case Item_Type::TRASH:
		return true;

	case Item_Type::NOT_TRASH:
		return false;

	default:
		std::cout << "\n!!!\tDefault case get_item_type()" << std::endl;
		std::exit(EXIT_FAILURE);
	}
}




void Item::make_volume(Item_Form form) {
	switch (form)
	{
	case Item_Form::RECTANGLE:
		polygon.point.push_back(x);
		polygon.point.push_back(y);
		polygon.point.push_back(x + x_stretch);
		polygon.point.push_back(y + y_stretch);
		break;

	default:
		std::cout << "\n!!!\tDefault case print_camera_state()" << std::endl;
		std::exit(EXIT_FAILURE);
	}
}

void Item::set_scale(double &x_, double &y_) {		// add sfml
	x_stretch = x_;
	y_stretch = y_;
}

// SFML

void Item::draw_item(sf::RenderWindow& window) {
	item_sprite.setPosition(static_cast<float>(x), static_cast<float>(y));
	window.draw(item_sprite);
}