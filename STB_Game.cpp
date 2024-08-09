#include "ccc_win.h"
#include "STB_Game.h" // STB_Board.h <-STB_Man.h, STB_Die.h

STB_Game::STB_Game()
{
	manCount = 12;
	dieCount = ceil(static_cast<double>(manCount) / 6.0);
	STB_Board initialBoard(manCount, dieCount);
	gameBoard = initialBoard;
	computerPlayerActive = false;
}

STB_Game::STB_Game(int numMen, int strategy, bool computerPlayer)
{
	manCount = numMen;
	dieCount = ceil(static_cast<double>(manCount) / 6.0);
	STB_Board initialBoard(manCount, dieCount);
	gameBoard = initialBoard;
	Computer_Player player(strategy);
	computerPlayerActive = computerPlayer;
}

int STB_Game::get_num_dice() const
{
	return dieCount;
}

void STB_Game::reset_board()
{
	STB_Board freshBoard(manCount, dieCount);
	gameBoard = freshBoard;
}

int STB_Game::roll_dice(string mess)
{
	bool rollingDice = true;
	int diceTotal = 0;
	Point clicked;

	draw_board(mess);

	while(rollingDice)
	{
		if (computerPlayerActive)
		{
			clicked = player.dice_roll();
		}
		else
		{
			clicked = cwin.get_mouse(mess);
		}

		// Checks to see if the user clicked reset
		if (gameBoard.on_reset(clicked))
		{
			reset_board();                          // Reset the board
			diceTotal = gameBoard.get_dice_total(); // Default dice total
			rollingDice = false;                    // Get out of loop
		}
		
		// Checks to see if the user clicked on a die
		if (gameBoard.on_dice(clicked))
		{
			gameBoard.roll_dice();                  // roll the dice
			diceTotal = gameBoard.get_dice_total(); // Get the dice total
			rollingDice = false;                    // Get out of loop
		}
	}
	return diceTotal;
}

void STB_Game::choose_men(int diceTotal, string mess)
{
	bool choosingMen = true;
	vector<int> indecesChosen; // to keep track of men chosen on current turn
	int menTotal = 0;
	int chosenMan = 0;
	Point clicked;
	vector<int> availableMen; 
	vector<Point> playerSelections;

	draw_board(mess);

	while(choosingMen)
	{
		// Clear the previous choices
		indecesChosen.clear();

		// Computer Simulation User
		if (computerPlayerActive)
		{
			// Get all available men values into a vector
			for (int i = 1; i <= manCount; i++)
			{
				if (gameBoard.man_available(i))
				{
					availableMen.push_back(i);
				}
			}

			/* Get a vector of the points on the board that correspond to the men chosen by the
			computer player (based on the strategy chosen) */
			playerSelections = player.select_men(availableMen, diceTotal, gameBoard.get_width_of_man(), gameBoard.get_width_of_space());

			/* Use the vector of points on the board corresponding the the computer player's choices
			to select the men.  This is implemented in the same way as if a person were playing, but
			getting the clicked points from a list and not the person */
			for (int i = 0; i < playerSelections.size(); i++)
			{
				clicked = playerSelections[i];                          // Get the next point in the vector
				if (gameBoard.on_man(chosenMan, clicked))               // Checks if the point is on an available man
				{
					gameBoard.flip_man(chosenMan);                      // Flip the man
					draw_board(mess);                                   // Redraw the board
					menTotal = gameBoard.get_men_total(indecesChosen);  // Get the total value of new men flipped and get an updated vector of indeces of newly flipped men
				
					if (menTotal == diceTotal)                          // Check to see if your total matches the dice
					{
						gameBoard.update_unselected_men(indecesChosen); // Use the list of chosen men to update the vector of available men
						choosingMen = false;                            // Get out of loop
					}
				}
			}
		}
		else // Human User
		{
			// Wait for the user to click somewhere on the board
			clicked = cwin.get_mouse(mess);

			// Checks to see if the user clicked reset
			if (gameBoard.on_reset(clicked))
			{
				reset_board();                          // reset the board
				diceTotal = gameBoard.get_dice_total(); // Default dice total
				choosingMen = false;                    // Get out of loop
			}

			// Checks to see if the user clicked a man
			if (gameBoard.on_man(chosenMan, clicked))
			{
				if (gameBoard.man_available(chosenMan))                 // If the man chosen is unselected
				{
					gameBoard.flip_man(chosenMan);                      // Flip the man
					draw_board(mess);                                   // Redraw the board
					menTotal = gameBoard.get_men_total(indecesChosen);  // Get the total value of new men flipped and get an updated vector of indeces of newly flipped men
				
					if (menTotal == diceTotal)                          // Check to see if your total matches the dice
					{
						gameBoard.update_unselected_men(indecesChosen); // Use the list of chosen men to update the vector of available men
						choosingMen = false;                            // Get out of loop
					}
				}
			}
		}
	}
}

bool STB_Game::check_win()
{
	for (int i = 1; i <= manCount; i++)
	{
		// If any man is still available, you still haven't won.
		if (gameBoard.man_available(i)) 
		{
			return false;
		}
	}
	return true;
}

bool STB_Game::check_lose()
{
	if (gameBoard.move_available())
	{
		return false;
	}
	return true;
}

void STB_Game::loseWin(string mess)
{
	bool resetting = true;
	Point clicked;

	draw_board(mess);

	while (resetting)
	{
		if (computerPlayerActive)
		{
			clicked = player.reset_board();
		}
		else
		{
			clicked = cwin.get_mouse(mess);
		}

		// Checks to see if the user clicked reset
		if (gameBoard.on_reset(clicked))
		{
			reset_board();                          // Reset the board
			resetting = false;                      // Get out of loop
		}
	}
}

void STB_Game::draw_board(string mess)
{
	if (!computerPlayerActive)
	{
		gameBoard.draw_board(mess);
	}
}