#include "ccc_win.h"
#include <vector>

class Computer_Player
{
public:
	/**
		Default Constructor
		sets strategy to 1
	*/
	Computer_Player();
	/**
		Constructor with given strategy
	*/
	Computer_Player(int strat);
	/**
		Gets a dice roll from the computer player
		@return Point where the right dice is
	*/
	Point dice_roll();
	/**
		Chooses the men for the current move
		@param unselectedMen vector of values of the men still left on the board
		@param diceTotal total currently showing on dice to match by selecting men
		@return vector of the selected men to complete the turn
	*/
	vector<Point> select_men(vector<int> unselectedMen, int diceTotal, int manWidth, int space);
	/**
		resets the board
		@return Point where the reset button is
	*/
	Point reset_board();
private:
	int strategy;
};