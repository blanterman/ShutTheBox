#pragma once
#include "ccc_win.h"
#include "STB_Element.h"

class STB_Man : public STB_Element
{
public:
	/**
		Default constructor of a man object
		sets select state to false (up), value to 0, and the location to (0, 0).
	*/
	STB_Man();
	/**
		Constructor of a man object with given settings
		@param sel selection state (should be false probably always)
		@param val position value of the man
		@param loc location of the lower left corner of the man on the grid
	*/
	STB_Man(bool sel, int val, Point loc);
	/**
		Sets or resets the selection state of the man
		@param sel selection state to set the man to
	*/
	void set_select(bool sel);
	/**
		Sets the position value of the man
		@param val number to set the position value of the man to
	*/
	void set_value(int val);
	/**
		Returns the current selection state of the man
		@return the current selection state of the man
	*/
	bool get_select() const;
	/**
		Returns the current position value of the man
		@return the current position value of the man
	*/
	int get_value() const;
	/**
		draws the man in the current state at the current location
	*/
	virtual void draw();
private:
	bool selected;
	int value;
};