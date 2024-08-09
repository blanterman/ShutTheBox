#include "ccc_win.h"
#include "STB_Man.h"

STB_Man::STB_Man()
	:STB_Element()
{
	selected = false;
	value = 0;
}

STB_Man::STB_Man(bool sel, int val, Point loc)
	:STB_Element(loc)
{
	selected = sel;
	value = val;
}

void STB_Man::set_select(bool sel)
{
	selected = sel;
}

void STB_Man::set_value(int val)
{
	value = val;
}


bool STB_Man::get_select() const
{
	return selected;
}

int STB_Man::get_value() const
{
	return value;
}

void STB_Man::draw()
{
	// Main rectangle
	Point p1 = STB_Element::get_location();
	Point p2 = p1;
	p2.move(24.0, 0.0);
	Line l1(p1, p2);
	Line l2 = l1;
	l2.move(0.0, 48.0);
	Point p3 = p1;
	p3.move(0.0, 48.0);
	Line l3(p1, p3);
	Line l4 = l3;
	l4.move(24.0, 0.0);

	cwin << l1 << l2 << l3 << l4;

	// Head Square
	Point p4 = p1;
	p4.move(6.0, selected ? 6.0 : 30.0); // place head on top or bottom depending on its selected state
	Point p5 = p4;
	p5.move(12.0, 0.0);
	Line l5(p4, p5);
	Line l6 = l5;
	l6.move(0.0, 12.0);
	Point p6 = p4;
	p6.move(0.0, 12.0);
	Line l7(p4, p6);
	Line l8 = l7;
	l8.move(12.0, 0.0);

	cwin << l5 << l6 << l7 << l8;
	
}