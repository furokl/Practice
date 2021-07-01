#include <iostream>

#include "enum_states.h"
#include "item.h"


Item::Item(double x_, double y_, Item_Type type_)
	: x(x_), y(y_), type(type_)
{
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