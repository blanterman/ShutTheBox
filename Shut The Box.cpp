/*	
	Shut the box dice game using Horstmann Graphics Libraries
	By Bryson Lanterman
	Version 1.1
	August 18, 2024

	V1.1 Updates:
		- Computer_Player.cpp: 
			+ Removes old valid man-selection finder function that only searced upto 4 elements.
			+ Fixes error in current man-selection finder functions.
			+ Removes strategy 3 and puts 4 to 3 because it wasn't really implemented.
			+ Adds strategy getter. Not used, but it was used to debug.
		- STB_Game.cpp:
			+ Fixes bug in constructor that wasn't allowing computer strategy to be set by user.
		- "Shut The Box.cpp":
			+ Updates user menu to show updated strategies
*/

#include "ccc_win.h"
#include "STB_Game.h"
#include <ctime>
#include <cstdlib>

static void welcome_screen()
{
	// Set arbitrary axis values
	int xmin = 0;
	int ymin = 323;
	int xmax = 400;
	int ymax = 0;
	//Sets the size of the board
	cwin.coord(xmin, ymin, xmax, ymax);

	string strategy1_1 = "1 always selects the option with the lowest quantity of men and the highest";
	string strategy1_2 = "value man.";
	string strategy2_1 = "2 always selects the option with the largest quantity of men with the lowest";
	string strategy2_2 = "values";
	string strategy3 = "3 random available choice";

	cwin.clear();

	Message welcome(Point(12.0, 300.0), "Welcome to Shut The Box. The most infuriating dice game ever.");

	Message strategyMenu(Point(12.0, 280.0), "SIMULATION STRATIES AVAILABLE:");
	Message messStrategy1_1(Point(12.0, 270.0), strategy1_1);
	Message messStrategy1_2(Point(12.0, 260.0), strategy1_2);
	Message messStrategy2_1(Point(12.0, 250.0), strategy2_1);
	Message messStrategy2_2(Point(12.0, 240.0), strategy2_2);
	Message messStrategy3(Point(12.0, 230.0), strategy3);

	cwin << welcome << strategyMenu << messStrategy1_1 << messStrategy1_2 << messStrategy2_1 << messStrategy2_2 << messStrategy3;
}

int ccc_win_main()
{
	bool cont = true;
	bool computerPlayer = false;
	int strategy = 1;	// 1 always selects the option with the lowest quantity of men and the highest value man.
						// 2 always selects the option with the largest quantity of men with the lowest values
						// 3 random available choice
	long maxGames = 0;
	int diceTotal = 0;
	long long numGames = 0;
	int numWins = 0;
	
	// Seeds the rand() function for dice rolls
	srand(time(NULL));

	// Messages to be displayed throughout the game
	string winMessage = "You Win! Winner! Please reset the board :)";
	string loseMessage = "You Lose! Loser! Please reset the board :)";
	string diceMessage = "Roll Dice by clicking on Dice";
	string selectMenMessage = "Select men to match total on dice";

	/******     Get Information from the User before the game Starts    */
	welcome_screen();
	int numMen = cwin.get_int("Input Number of Men (12 is standard): ");
	string resp = cwin.get_string("Run Simulations? (y/n) ");

	if (resp == "y")
	{
		computerPlayer = true;
		maxGames = stol(cwin.get_string("How many games do you want to simulate? "));
		strategy = cwin.get_int("Which strategy would you like to simulate? ");
	}

	cwin.clear();

	/********    Done getting information from user                     */


	// START THE GAME
	STB_Game game(numMen, strategy, computerPlayer);

	/*******    Main Game Loop    ********/
	while (cont)
	{
		// Waits for the player to click the dice then totals them
		diceTotal = game.roll_dice(diceMessage);

		// Reset was not selected and we have a valid dice total
		if (diceTotal != game.get_num_dice() * 7)
		{
			// Checks all available moves, if none match the dice, you lose
			if (game.check_lose())
			{
				// Computer Simulation updates
				if (computerPlayer)
				{
					numGames++;
					if (numGames < maxGames)
					{
						game.loseWin(loseMessage);
					}
					else
					{
						cwin.clear();
						Message wins(Point(12.0, 161.0), to_string(static_cast<long long>(numWins)) + " Wins out of " + to_string(static_cast<long long>(maxGames)) + " games.");
						cwin << wins;
						cont = false;
					}
				}
				else // Player informed of loss
				{
					game.loseWin(loseMessage);
				}
			}
			else // You haven't lost, move on to selecting the men
			{
				game.choose_men(diceTotal, selectMenMessage);
			}
		}

		// Checks to see if you've won by seeing if any men are available after your move
		if (game.check_win())
		{
			// Computer Simulation updates
			if (computerPlayer)
			{
				numGames++;
				numWins++;
				if (numGames < maxGames)
				{
					game.loseWin(winMessage);
				}
				else
				{
					cwin.clear();
					Message wins(Point(12.0, 161.0), to_string(static_cast<long long>(numWins)) + " Wins out of " + to_string(static_cast<long long>(maxGames)) + " games.");
					cwin << wins;
					cont = false;
				}
			}
			else // Player informed of Win
			{
				game.loseWin(winMessage);
			}
		}
	}

	return 0;
}