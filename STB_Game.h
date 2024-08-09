#include "ccc_win.h"
#include "STB_Board.h"
#include "Computer_Player.h"

class STB_Game
{
public:
	/**
		Default constructor of a game with initial conditions of 12 men and 2 dice
	*/
	STB_Game();
	/**
		Starts a game by initializing a board with game start conditions and given number of men
		@param numMen number of men on the board
		@param strat strategy of the computer player if there is one.
		@param computerPlayer true if the computer player will be used.
	*/
	STB_Game(int numMen, int strat, bool computerPlayer);
	/**
		Returns the number of dice set by constructor
	*/
	int get_num_dice() const;
	/**
		Returns a game to starting conditions
	*/
	void reset_board();
	/**
		Implements a dice roll by the player consisting
		@return value of the dice summed
	*/
	int roll_dice(string mess);
	/**
		Prompts the user to choose the men to try to reach the sum of the dice
		@param current sum of the dice
	*/
	void choose_men(int diceTotal, string mess);
	/**
		Checks to see if the player has won
		@return true if there are no more unselected men
	*/
	bool check_win();
	/**
		Checks to see if the player has lost the game
		@return true if there are no more ways to match the total on the dice
	*/
	bool check_lose();
	/**
		Displays instructions for the loser;
	*/
	void loseWin(string mess);
	/**
		Access to the draw function in the board class
	*/
	void draw_board(string mess);

private:
	STB_Board gameBoard;
	int manCount;
	int dieCount;
	Computer_Player player;
	bool computerPlayerActive;
};