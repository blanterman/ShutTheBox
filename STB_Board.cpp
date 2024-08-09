#include "ccc_win.h"
#include "STB_Board.h"

const int RESET_WIDTH = 23;
const int SPACE = 1;
const int MAN_WIDTH = 24;
const double DICE_WIDTH = 36.5;
const int BUFFER = 12;
const double CHAR_TO_LENGTH = 2.64; // Determined empically by looking at messages on board of this size


/**
	Returns the maximum number of factors in the given vector of values that can be used to sum to a given value
	This assumes that the vector is sorted previous to this function call
	This is done by summing the lowest elements in the vector until we get a sum greater than the value.
	@param vals a vector of integer values
	@param value an integer value for which we are checking the maximum possible factors
	@return maximum number of elements in vals that will sum to value
*/
int find_max_factors(const std::vector<int>& vals, int value)
{
	int numFactors = 0;
	int total = 0;
	for (int i = 0; i < vals.size(); i++)
	{
		total += vals[i];
		if (total <= value)
		{
			numFactors++;
		}
		else
		{
			return numFactors;
		}
	}
	return numFactors;
}

bool in_last_spot(std::vector<int>& indeces, const std::vector<int>& vals)
{
	int lastInd = vals.size() - 1;
	for (int i = indeces.size() - 1; i >= 0; i--)
	{
		if (indeces[i] != lastInd)
		{
			return false;
		}
		lastInd--;
	}
	return true;
}

int find_lastMoveable(std::vector<int>& indeces, const std::vector<int>& vals)
{
	int lastInd = vals.size() - 1;
	for (int i = indeces.size() - 1; i >= 0; i--)
	{
		if (indeces[i] != lastInd)
		{
			return i;
		}
		lastInd--;
	}
	return -1;
}

bool find_get_next(std::vector<int>& indeces, const std::vector<int>& vals)
{
	int indMoveable = 0;
	int refPosition = 0;
	if (in_last_spot(indeces, vals))
	{	
		return false;
	}
	indMoveable = find_lastMoveable(indeces, vals);
	refPosition = indeces[indMoveable] + 1;
	for (int i = indMoveable; i < indeces.size(); i++)
	{
		indeces[i] = refPosition;
		refPosition++;
	}
	return true;
}

bool find_part2(std::vector<int> indeces, const std::vector<int>& vals, int value)
{
	bool cont = true;
	int sum = 0;
	std::vector<int> valsAtIndeces;
	while (cont)
	{
		sum = 0;
		for (int i = 0; i < indeces.size(); i++)
		{
			sum += vals[indeces[i]];
		}
		if (sum == value)
		{
			return true;
		}
		if (!find_get_next(indeces, vals))
		{
			cont = false;
		}
	}
	return false;
}
/**
	Return true if a combination of values in the given vector can be summed to the given value.
	This is the entry point to use other functions that will first narrow down the number of values
	that need to be summed, moving to the next set of values to be summed, then summing them to 
	check if they are equal to value. First all single values will be checked, then the sum of two,
	then the sum of 3 and so on until not needed.
	@param vals vector of integers of available values
	@param integer value the value to be summed to 
*/
bool find_part(const std::vector<int>& vals, int value)
{
	std::vector<int> indeces;
	bool moveAvailable = false;
	int maxLevel = find_max_factors(vals, value);
	for (int i = 0; i < maxLevel; i++)
	{
		indeces.push_back(i);
		moveAvailable = find_part2(indeces, vals, value);
		if (moveAvailable)
		{
			return true;
		}
	}
	return false;
}

STB_Board::STB_Board()
{
	manCount = 12;
	dieCount = dieCount = ceil(static_cast<double>(manCount) / 6.0);

	const int XMIN = 0;
	const int YMIN = 323;
	const int XMAX = (manCount * MAN_WIDTH) + ((manCount - 1) * SPACE) + (2 * BUFFER);
	const int YMAX = 0;
	//Sets the size of the board
	cwin.coord(XMIN, YMIN, XMAX, YMAX);

	// Populate the element vector with men at the right location and with the right value
	bool initialState = false;
	Point locFirst(-(BUFFER + SPACE), 235.0);
	Point loc = locFirst;
	for (int i = 0; i < manCount; i++)
	{
		loc.move(static_cast<double>(MAN_WIDTH + SPACE), 0.0);
		elements.push_back(new STB_Man(initialState, i + 1, loc));
		unselectedMen.push_back(i);
	}
	
	// Populate the element vector with 2 dice with the right location and a value of 7.
	locFirst = Point(static_cast<double>(BUFFER) - DICE_WIDTH - static_cast<double>(SPACE), 75.0);
	loc = locFirst;
	for (int i = 0; i < dieCount; i++)
	{
		loc.move(DICE_WIDTH + static_cast<double>(SPACE), 0.0);
		elements.push_back(new STB_Die(loc));
	}

	widthMan = MAN_WIDTH;
	widthSpace = SPACE;
}

STB_Board::STB_Board(int numMen, int numDice)
{
	manCount = numMen;
	dieCount = numDice;

	int xmin = 0;
	int ymin = 323;
	int xmax = (manCount * MAN_WIDTH) + ((manCount - 1) * SPACE) + (2 * BUFFER);
	int ymax = 0;
	//Sets the size of the board
	cwin.coord(xmin, ymin, xmax, ymax);

	// Populate the element vector with men at the right location and with the right value
	bool initialState = false;
	Point locFirst(-(BUFFER + SPACE), 235.0);
	Point loc = locFirst;
	for (int i = 0; i < manCount; i++)
	{
		loc.move(static_cast<double>(MAN_WIDTH + SPACE), 0.0);
		elements.push_back(new STB_Man(initialState, i + 1, loc));
		unselectedMen.push_back(i);
	}
	
	// Populate the element vector with dice with the right location and a value of 7.
	locFirst = Point(static_cast<double>(BUFFER) - DICE_WIDTH - static_cast<double>(SPACE), 75.0);
	loc = locFirst;
	for (int i = 0; i < dieCount; i++)
	{
		loc.move(DICE_WIDTH + static_cast<double>(SPACE), 0.0);
		elements.push_back(new STB_Die(loc));
	}

	widthMan = MAN_WIDTH;
	widthSpace = SPACE;
}

void STB_Board::flip_man(int val)
{
	int index = val - 1; // get index from value
	elements[index]->set_select(!(elements[index]->get_select())); // flip the state
}

void STB_Board::roll_dice()
{
	for (int i = manCount; i < elements.size(); i++)
	{
		elements[i]->roll_die();
	}
}

bool STB_Board::on_man(int& val, Point clicked)
{
	int leftSide = 0;
	int rightSide = 0;
	for (int i = 0; i < manCount; i++)
	{
		leftSide = BUFFER + ((MAN_WIDTH + SPACE) * i);
		rightSide = leftSide + MAN_WIDTH;
		if (leftSide <= clicked.get_x() && clicked.get_x() <= rightSide && 235.0 <= clicked.get_y() && clicked.get_y() <= 293.0)
		{
			val = i + 1;
			return true;
		}
	}
	return false;
}

bool STB_Board::on_dice(Point clicked)
{
	double leftSide = 0;
	double rightSide = 0;
	double bottom = 75.0;
	double top = bottom + DICE_WIDTH;
	for (int i = 0; i < dieCount; i++)
	{
		leftSide = BUFFER + ((DICE_WIDTH + SPACE) * i);
		rightSide = leftSide + DICE_WIDTH;
		if (leftSide <= clicked.get_x() && clicked.get_x() <= rightSide && bottom <= clicked.get_y() && clicked.get_y() <= top)
		{
			return true;
		}
	}
	return false;
}

bool STB_Board::on_reset(Point clicked)
{
	// reset button
	if (BUFFER <= clicked.get_x() && clicked.get_x() <= (BUFFER + RESET_WIDTH) && 0.0 <= clicked.get_y() && clicked.get_y() <= RESET_WIDTH)
	{
		return true;
	}
	return false;
}

int STB_Board::get_dice_total() const
{
	int total = 0;
	// Sum the current values on the dice
	for (int i = manCount; i < elements.size(); i++)
	{
		total += elements[i]->get_value();
	}
	return total;
}

int STB_Board::get_width_of_man() const
{
	return widthMan;
}

int STB_Board::get_width_of_space() const
{
	return widthSpace;
}

bool STB_Board::man_available(int val)
{
	// get the index of the given man from the value
	int index = val - 1;

	// Check the vector of valid indeces (indeces of unselected men) for the index
	for (int i = 0; i < unselectedMen.size(); i++)
	{
		if (unselectedMen[i] == index)
		{
			return true; // index found
		}
	}
	return false; // index not found
}

bool STB_Board::move_available()
{
	vector<int> values;

	// Use the vector of indices of available men to populate a vector of just the values of the currently available men
	for (int i = 0; i < unselectedMen.size(); i++)
	{
		values.push_back(elements[unselectedMen[i]]->get_value());
	}

	return find_part(values, get_dice_total()); // Search all partitions of values and see if any match the current dice value
}

int STB_Board::get_men_total(vector<int>& chosenIndeces) const
{
	// initialize total for current turn
	int totalMen = 0;

	// Iterate through the list of men not used in previous turns.
	// At this point the list of unselected men will have unselected men and the potentially selected men from the current turn
	// This adds up only the potentially selected men
	for (int i = 0; i < unselectedMen.size(); i++)
	{
		// If the man is still available and selected
		if (elements[unselectedMen[i]]->get_select())
		{
			chosenIndeces.push_back(unselectedMen[i]); // Put the index in the chosen list
			totalMen += elements[unselectedMen[i]]->get_value(); //Add the value to the total
		}
	}
	return totalMen;
}

void STB_Board::update_unselected_men(const vector<int>& chosenIndeces)
{
	// Upon a valid and final move, chosenIndeces is the list of indeces of the men used
	// These indeces are now removed from the list of available indeces (unselectedMen)

	// For all the chosen indeces...
	for (int j = 0; j < chosenIndeces.size(); j++)
	{
		// ...search through the available indeces for a match...
		for (int i = 0; i < unselectedMen.size(); i++)
		{
			// ...when the match is found...
			if (unselectedMen[i] == chosenIndeces[j])
			{
				// delete the value because it has been used and is no longer valid.
				unselectedMen.erase(unselectedMen.begin() + i);
				i--; // update this because now there is one less element
			}
		}
	}
}

void STB_Board::draw_board(string mess)
{
	cwin.clear(); // Clears board

	// Redraws all elements with the current states and values
	for (int i = 0; i < elements.size(); i++)
	{
		elements[i]->draw();
	}

	Point ref(-3.0, 295.0);
	// Redraws all numbers of the active men
	for (int i = 0; i < manCount; i++) // go through all numbers
	{
		ref.move(static_cast<double>(MAN_WIDTH + SPACE), 0.0); // Move to the first/next location
		for (int j = 0; j < unselectedMen.size(); j++) // go through the unselected men
		{
			if (unselectedMen[j] == i) // check if there is an active man that is in that location
			{
				cwin << Message(ref, static_cast<double>(i + 1)); // place the number if there is an active man
			}
			
		}
		
	}

	// Draw reset button
	Point p1(BUFFER, 0.0);
	Point p2 = p1;
	p2.move(0.0, RESET_WIDTH);
	Line l1(p1, p2);
	Line l2 = l1;
	l2.move(RESET_WIDTH, 0.0);
	Point p3 = p1;
	p3.move(RESET_WIDTH, 0.0);
	Line l3(p1, p3);
	Line l4 = l3;
	l4.move(0.0, RESET_WIDTH);

	// Reset text
	Message m1(Point(BUFFER + 3.0, 14.0), "Reset");

	// Info message text
	//double offset = static_cast<double>(mess.length() / 2.0) * CHAR_TO_LENGTH; // calculate the offset for centering the message
	Message m2(Point(BUFFER, 190.0), mess);

	cwin << l1 << l2 << l3 << l4 << m1 << m2;
}