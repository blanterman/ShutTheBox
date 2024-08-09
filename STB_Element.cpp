#include "ccc_win.h"
#include "STB_Element.h"

STB_Element::STB_Element()
{
	location = Point(0.0, 0.0);
}

STB_Element::STB_Element(Point loc)
{
	location = loc;
}

void STB_Element::set_location(Point loc)
{
	location = loc;
}

void STB_Element::set_select(bool sel)
{

}

void STB_Element::roll_die()
{

}

bool STB_Element::get_select() const
{
	return false;
}

int STB_Element::get_value() const
{
	return 1;
}

Point STB_Element::get_location() const
{
	return location;
}

void STB_Element::draw()
{

}