#pragma once
#include "ccc_win.h"

class STB_Element
{
public:
	/**
		Default constructor location at (0,0)
	*/
	STB_Element();
	/**
		Constructor of element at given Point location
		@param loc location of element
	*/
	STB_Element(Point loc);
	/**
		Sets/Resets the location of the bottom left corner of the element
		@param loc point location to set
	*/
	void set_location(Point loc);
	/**
		Sets the selection state of this element
	*/
	virtual void set_select(bool sel);
	/**
		"rolls" the die and returns the new value
		@return value of the roll
	*/
	virtual void roll_die();
	/**
		Returns the location of the bottom left corner of the element
	*/
	Point get_location() const;
	/**
		Returns the selection state of the element
	*/
	virtual bool get_select() const;
	/**
		Gets the latest "rolled" die value
		@return the current value of die
	*/
	virtual int get_value() const;
	/**
		Draws the element
	*/
	virtual void draw();
private:
	Point location;
};