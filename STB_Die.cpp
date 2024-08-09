#include "ccc_win.h"
#include "STB_Die.h"
#include <cstdlib>
#include <ctime>

STB_Die::STB_Die()
	:STB_Element()
{
	value = 7;
}

STB_Die::STB_Die(Point loc)
	:STB_Element(loc)
{
	value = 7;
}

void STB_Die::roll_die()
{
	value = (rand() % 6) + 1;
}

int STB_Die::get_value() const
{
	return value;
}

void STB_Die::draw()
{
	double width = 36.5;
	// Square outline
	Point p1 = STB_Element::get_location();
	Point p2 = p1;
	p2.move(width, 0.0);
	Line l1(p1, p2);
	Line l2 = l1;
	l2.move(0.0, width);
	Point p3 = p1;
	p3.move(0.0, width);
	Line l3(p1, p3);
	Line l4 = l3;
	l4.move(width, 0.0);

	cwin << l1 << l2 << l3 << l4;

	const double RADIUS = 3; // Radius of dots on the die

	// If the die has a value of 2, 3, 4, 5, 6, or 7 (7 used for debugging), draw the top left dot
	// and the bottom right dot
	if (2 <= value && value <= 7)
	{
		// Top left
		Point p4 = STB_Element::get_location();
		p4.move(width / 6.0, width * 5.0 / 6.0);
		Circle c1(p4, RADIUS);

		// bottom right
		Point p10 = STB_Element::get_location();
		p10.move(width * 5.0 / 6.0, width / 6.0);
		Circle c7(p10, RADIUS);

		cwin << c1 << c7;
	}

	// If the die has a value of 4, 5, 6, or 7 (7 used for debugging), draw the top right dot
	// and the bottom left dot
	if (4 <= value && value <= 7)
	{
		// Top Right
		Point p5 = STB_Element::get_location();
		p5.move(width * 5.0 / 6.0, width * 5.0 / 6.0);
		Circle c2(p5, RADIUS);
		
		// Bottom Left
		Point p6 = STB_Element::get_location();
		p6.move(width / 6.0, width / 6.0);
		Circle c3(p6, RADIUS);
		
		cwin << c2 << c3;
	}

	// If the die has a value of 6 or 7 (7 used for debugging), draw the middle left dot
	// and the middle right dot
	if (6 <= value && value <= 7)
	{
		// Middle Left
		Point p7 = STB_Element::get_location();
		p7.move(width / 6.0, width / 2.0);
		Circle c4(p7, RADIUS);
		cwin << c4;

		// Middle Right
		Point p9 = STB_Element::get_location();
		p9.move(width * 5.0 / 6.0, width / 2.0);
		Circle c6(p9, RADIUS);
		cwin << c6;
	}

	// If the die has an odd value - 1, 3, 5, or 7 (7 used for debugging), draw the middle middle dot
	if (value % 2 == 1)
	{
		// Middle Middle
		Point p8 = STB_Element::get_location();
		p8.move(width / 2.0, width / 2.0);
		Circle c5(p8, RADIUS);
		cwin << c5;
	}

}