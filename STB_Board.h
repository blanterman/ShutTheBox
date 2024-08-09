#include "ccc_win.h"
#include "STB_Man.h" // inherits from STB_Element
#include "STB_Die.h" // inherits from STB_Element
#include <vector>

class STB_Board
{
public:
	/**
		Default constructor of a game board that initializes all the men and dice into the elements vector
	*/
	STB_Board();
	/**
		Default constructor of a game board that initializes all the men and dice into the elements vector
		@param numMen number of men on the board
		@param numDice number of dice on the board
	*/
	STB_Board(int numMen, int numDice);
	/**
		Sets the selection state of the given man number
		@param value (position) of the man whos state needs to flip
	*/
	void flip_man(int val);
	/**
		Rolls the dice and updates their values
	*/
	void roll_dice();
	/**
		Returns true if the point given is over a man, also sets the given value to the value of the clicked man
		@param referenced integer value of the man clicked
		@param point clicked
		@return true if over a man
	*/
	bool on_man(int& val, Point clicked);
	/**
		Returns true if the point given is over a die
		@param point clicked
		@return true if over a man
	*/
	bool on_dice(Point clicked);
	/**
		Returns true if the point given of over the reset button
		@param point clicked
		@return true if over reset area
	*/
	bool on_reset(Point clicked);
	/**
		Returns the total of the dice values
		@return sum of dice
	*/
	int get_dice_total() const;
	/**
		Returns the width of the man
		@return width of man
	*/
	int get_width_of_man() const;
	/**
		Returns the width of the space between men and between dice
		@return width of the space
	*/
	int get_width_of_space() const;
	/**
		Return true if the mans index is in the unselectedMen vector
		@return true if unselected
	*/
	bool man_available(int val);
	/**
		Return true if you can add up the remaining men in some way to match the value on the dice
		@return true if move possible
	*/
	bool move_available();
	/**
		Returns the sum of the values of selected men
		@return sum of selected men
	*/
	int get_men_total(vector<int>& chosenIndeces) const;
	/**
		Updates the unselectedMen vector by removing the indeces of the latest valid turn
	*/
	void update_unselected_men(const vector<int>& chosenIndeces);
	/**
		Draws the board with all the elements with current values
	*/
	void draw_board(string mess);
private:
	vector<STB_Element*> elements;
	vector<int> unselectedMen;
	int manCount;
	int dieCount;
	int widthMan;
	int widthSpace;
};