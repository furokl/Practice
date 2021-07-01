#ifndef ITEM_H
#define ITEM_H

class Item
{
private:
	double x, y;
	Item_Type type{};
	// add length + enum figure_type + (struct points?)
public:
	Item(double, double, Item_Type);
	void get_coord(double&, double&);
	bool get_item_type();
};

#endif // !ITEM_H