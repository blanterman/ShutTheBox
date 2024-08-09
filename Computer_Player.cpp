#include "ccc_win.h"
#include "Computer_Player.h"


int max_factors(const std::vector<int>& vals, int value)
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

bool last_spot(std::vector<int>& indeces, const std::vector<int>& vals)
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

int lastMoveable(std::vector<int>& indeces, const std::vector<int>& vals)
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

bool get_next(std::vector<int>& indeces, const std::vector<int>& vals)
{
	int indMoveable = 0;
	int refPosition = 0;
	if (last_spot(indeces, vals))
	{	
		return false;
	}
	indMoveable = lastMoveable(indeces, vals);
	refPosition = indeces[indMoveable] + 1;
	for (int i = indMoveable; i < indeces.size(); i++)
	{
		indeces[i] = refPosition;
		refPosition++;
	}
	return true;
}

void part2(std::vector<int> indeces, const std::vector<int>& vals, int value, std::vector<std::vector<int>>& parts)
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
			for (int i = 0; i < indeces.size(); i++)
			{
				valsAtIndeces.push_back(vals[indeces[i]]);
			}
			parts.push_back(valsAtIndeces);
		}
		if (!get_next(indeces, vals))
		{
			cont = false;
		}
	}
}

std::vector<std::vector<int>> part(const std::vector<int>& vals, int value)
{
	std::vector<int> indeces;
	std::vector<std::vector<int>> parts;
	int maxLevel = max_factors(vals, value);
	for (int i = 0; i < maxLevel; i++)
	{
		indeces.push_back(i);
		part2(indeces, vals, value, parts);
	}
	return parts;
}

vector<vector<int>> get_partitions2(const std::vector<int>& vals, int value)
{
	int total = 0;
	int first = 0;
	int second = 0;
	int third = 0;
	int fourth = 0;

	vector<vector<int>> parts;
	vector<int> factors;

	int maxFactors = 0;
	maxFactors = max_factors(vals, value);
	
	// quadruples
	if (maxFactors >= 4)
	{
		for (int i = 0; i < vals.size(); i++)
		{
			first = vals[i];
			for (int j = i; j < vals.size() - 1; j++)
			{
				second = vals[j + 1];
				for (int k = j; k < vals.size() - 2; k++)
				{
					third = vals[k + 2];
					for (int m = k; m < vals.size() - 3; m++)
					{
						fourth = vals[m + 3];
						total = first + second + third + fourth;
						factors.clear();
						if (total == value)
						{
							factors.push_back(first);
							factors.push_back(second);
							factors.push_back(third);
							factors.push_back(fourth);
							parts.push_back(factors);
						}
						if (total > value)
						{
							m = vals.size() - 3;
						}
					}
				}
			
			}
		}
	}
	// triples
	if (maxFactors >= 3)
	{
		for (int i = 0; i < vals.size(); i++)
		{
			first = vals[i];
			for (int j = i; j < vals.size() - 1; j++)
			{
				second = vals[j + 1];
				for (int k = j; k < vals.size() - 2; k++)
				{
					third = vals[k + 2];
					total = first + second + third;
					factors.clear();
					if (total == value)
					{
						factors.push_back(first);
						factors.push_back(second);
						factors.push_back(third);
						parts.push_back(factors);
					}
					if (total > value) 
					{
						k = vals.size() - 2;
					}
				}
			}
		}
	}
	
	// doubles
	if (maxFactors >= 2)
	{
		for (int i = 0; i < vals.size(); i++)
		{
			first = vals[i];
			for (int j = i; j < vals.size() - 1; j++)
			{
				second = vals[j + 1];
				total = first + second;
				factors.clear();
				if (total == value)
				{
					factors.push_back(first);
					factors.push_back(second);
					parts.push_back(factors);
				}
				if (total > value)  
				{
					j = vals.size() - 1;
				}
				
			}
		}
	}
	//singles
	if (maxFactors >= 1)
	{
		for (int i = 0; i < vals.size(); i++)
		{
			first = vals[i];
			total = first;
			factors.clear();
			if (total == value)
			{
				factors.push_back(first);
				parts.push_back(factors);
			}
			if (total > value) 
			{
				i = vals.size();
			}
			
		}
	}
	return parts;
}



vector<Point> vals_to_points(const vector<int>& vals, int manWidth, int space)
{
	vector<Point> points;
	for (int i = 0; i < vals.size(); i++)
	{
		points.push_back(Point(static_cast<double>(manWidth + space) * vals[i] - static_cast<double>(space), 264.0));
	}
	return points;
}

Computer_Player::Computer_Player()
{
	strategy = 1;
}

Computer_Player::Computer_Player(int strat)
{
	strategy = strat;
}

Point Computer_Player::dice_roll()
{
	// clicks first die on the left
	return Point(13.0, 111.0);
}

vector<Point> Computer_Player::select_men(vector<int> unselectedMen, int diceTotal, int manWidth, int space)
{
	vector<vector<int>> options;
	vector<int> selection_vals;
	// Best Strategy so far
	if (strategy == 1)
	{
		options = part(unselectedMen, diceTotal);
		selection_vals = options[0];
	}
	// A little worse than strategy 1
	if (strategy == 2)
	{
		options = get_partitions2(unselectedMen, diceTotal);
		selection_vals = options[options.size() - 1];
	}
	// Worse Strategy
	if (strategy == 3)
	{
		options = part(unselectedMen, diceTotal);
		selection_vals = options[options.size() - 1];
	}
	// Random Strategy
	if (strategy == 4)
	{
		options = part(unselectedMen, diceTotal);
		selection_vals = options[rand() % options.size()];
	}
	
	vector<Point> selection = vals_to_points(selection_vals, manWidth, space);
	return selection;
}

Point Computer_Player::reset_board()
{
	return Point(12.0, 12.0);
}