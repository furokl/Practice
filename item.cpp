#include <iostream>

#include "enum_states.h"
#include "control_system.h"

#include "item.h"


Item::Item(float x_, float y_, Item_Type type_, Item_Form form_)
	: x(x_), y(y_), type(type_), form(form_)
{
	make_volume(form_);

	item_texture.loadFromFile("C:\\Users\\User\\source\\repos\\RoboTrash_SFML\\redist\\item.png");
	item_texture.setSmooth(true);
	item_sprite.setTexture(item_texture);

	trash_can_texture.loadFromFile("C:\\Users\\User\\source\\repos\\RoboTrash_SFML\\redist\\trash_can.png");
	trash_can_texture.setSmooth(true);
	trash_can_sprite.setTexture(trash_can_texture);
}

void Item::set_coord(float& x_, float& y_) {
	x = x_;
	y = y_;
}

float Item::get_coord_x() {
	return x;
}

float Item::get_coord_y() {
	return y;
}

Item_Type Item::get_item_type() {
	switch (type)
	{
	case Item_Type::TRASH:
		return Item_Type::TRASH;

	case Item_Type::NOT_TRASH:
		return Item_Type::NOT_TRASH;

	case Item_Type::TRASH_CAN:
		return Item_Type::TRASH_CAN;

	default:
		std::cout << "\n!!!\tDefault case get_item_type()" << std::endl;
		std::exit(EXIT_FAILURE);
	}
}

void Item::set_item_type() {
	type = Item_Type::NOT_TRASH;
}

void Item::make_volume(Item_Form form) {
	x_stretch = control_system::item_stretch;
	y_stretch = control_system::item_stretch;

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



// SFML

void Item::draw_item(sf::RenderWindow &window) {
	item_sprite.setPosition(x, y);
	item_sprite.move(
		control_system::item_displacement,
		control_system::item_displacement);
	window.draw(item_sprite);
}

void Item::draw_trash_can(sf::RenderWindow &window) {
	trash_can_sprite.setPosition(x, y);
	trash_can_sprite.move(
		control_system::can_displacement,
		control_system::can_displacement);

	window.draw(trash_can_sprite);
}