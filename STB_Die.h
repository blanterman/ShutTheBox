#pragma once
#include "ccc_win.h"
#include "STB_Element.h"

class STB_Die : public STB_Element
{
public:
	/**
		Default constructor of the die object
		sets value to 6 and location to (0,0)
	*/
	STB_Die();
	/**
		Constructor for the die object with the given location and value set to 7
	*/
	STB_Die(Point loc);
	/**
		"rolls" the die and returns the new value
		@return value of the roll
	*/
	virtual void roll_die();
	/**
		Gets the latest "rolled" die value
		@return the current value of die
	*/
	virtual int get_value() const;
	/**
		Draws the die on the grid at the location 
	*/
	virtual void draw();
private:
	int value;
};