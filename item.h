#ifndef ITEM_H
#define ITEM_H
#include <iostream> // del
#include <vector>
class Item
{
private:
	double x, y, x_stretch{ 1.0 }, y_stretch{ 1.0 };
	struct Polygon {
		std::vector<double> point;
	};
	Item_Type type;
	Item_Form form;
	
public:
	Polygon polygon;
	Item(double, double, Item_Type, Item_Form);
	void get_coord(double&, double&);
	bool get_item_type();
	void make_volume(Item_Form form);
	void set_scale(double&, double&);
};

#endif // !ITEM_H