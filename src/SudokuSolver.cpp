// SudokuSolver.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include <iostream>
using namespace std;

class SudokuSolver
{
private:
	int validValues[27][27];
	int solutionValues[9][9];
	int puzzleValues[8][9][9] = {
	{
		{ 2,0,0,8,0,4,0,0,6 },
		{ 0,0,6,0,0,0,5,0,0 },
		{ 0,7,4,0,0,0,9,2,0 },
		{ 3,0,0,0,4,0,0,0,7 },
		{ 0,0,0,3,0,5,0,0,0 },
		{ 4,0,0,0,6,0,0,0,9 },
		{ 0,1,9,0,0,0,7,4,0 },
		{ 0,0,8,0,0,0,2,0,0 },
		{ 5,0,0,6,0,8,0,0,1 }
	},
	{
		{ 4,0,0,2,0,7,0,0,9 },
		{ 0,3,0,8,0,4,0,6,0 },
		{ 0,0,8,1,5,6,7,0,0 },
		{ 6,1,4,0,0,0,2,7,5 },
		{ 0,0,5,0,0,0,4,0,0 },
		{ 8,7,2,0,0,0,9,3,1 },
		{ 0,0,6,3,2,9,5,0,0 },
		{ 0,8,0,5,0,1,0,9,0 },
		{ 1,0,0,6,0,8,0,0,7 }
	},
	{
		{ 3,0,2,0,7,0,5,0,4 },
		{ 0,0,0,0,0,0,0,0,0 },
		{ 0,0,6,2,5,4,0,0,0 },
		{ 0,9,0,0,0,0,6,0,0 },
		{ 0,0,8,9,6,5,1,0,0 },
		{ 0,0,5,0,0,0,0,2,0 },
		{ 0,0,0,1,9,7,8,0,0 },
		{ 0,0,0,0,0,0,0,0,0 },
		{ 5,0,7,0,8,0,2,0,6 }
	},
	{
		{ 4,8,7,0,0,0,0,6,0 },
		{ 0,6,0,0,0,0,2,0,3 },
		{ 5,0,0,9,0,0,0,0,0 },
		{ 0,5,4,0,0,9,3,0,0 },
		{ 0,0,0,8,0,6,0,0,0 },
		{ 0,0,6,5,0,0,8,2,0 },
		{ 0,0,0,0,0,2,0,0,7 },
		{ 3,0,8,0,0,0,0,1,0 },
		{ 0,2,0,0,0,0,6,4,8 }
	},
	{
		{ 0,0,9,0,0,0,0,6,0 },
		{ 0,0,0,2,0,7,0,5,0 },
		{ 2,0,0,0,6,0,8,0,9 },
		{ 0,0,0,0,0,0,9,0,0 },
		{ 0,2,5,3,0,9,7,1,0 },
		{ 0,0,3,0,0,0,0,0,0 },
		{ 3,0,1,0,4,0,0,0,6 },
		{ 0,6,0,8,0,1,0,0,0 },
		{ 0,7,0,0,0,0,3,0,0 }
	},
	{
		{ 0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,3,0,8,5 },
		{ 0,0,1,0,2,0,0,0,0 },
		{ 0,0,0,5,0,7,0,0,0 },
		{ 0,0,4,0,0,0,1,0,0 },
		{ 0,9,0,0,0,0,0,0,0 },
		{ 5,0,0,0,0,0,0,7,3 },
		{ 0,0,2,0,1,0,0,0,0 },
		{ 0,0,0,0,4,0,0,0,9 }
	},
	{
		{ 0,9,0,0,2,0,0,0,8 },
		{ 0,0,0,0,0,0,0,4,0 },
		{ 2,3,0,0,0,0,0,0,1 },
		{ 0,6,0,0,0,5,4,0,0 },
		{ 0,0,0,0,0,0,1,0,0 },
		{ 9,0,0,0,8,7,3,0,6 },
		{ 3,0,0,0,7,0,0,0,0 },
		{ 0,0,6,0,9,3,0,0,0 },
		{ 0,0,1,0,5,0,0,0,7 }
	}, 
	{
		{ 0,0,0,7,0,0,0,0,0 },
		{ 1,0,0,0,0,0,0,0,0 },
		{ 0,0,0,4,3,0,2,0,0 },
		{ 0,0,0,0,0,0,0,0,6 },
		{ 0,0,0,5,0,9,0,0,0 },
		{ 0,0,0,0,0,0,4,1,8 },
		{ 0,0,0,0,8,1,0,0,0 },
		{ 0,0,2,0,0,0,0,5,0 },
		{ 0,4,0,0,0,0,3,0,0 }
	} 
};

public:
	SudokuSolver()
	{
		Reset();
	}

	// Clear the solution values and set the initial values for the valid values table
	void Reset()
	{
		memset(solutionValues, 0, sizeof(int) * 9 * 9);
		for (int i = 0; i<27; i++)
		{
			for (int j = 0; j<27; j++)
			{
				validValues[i][j] = (j % 3) + ((i % 3) * 3) + 1;
			}
		}
	}

	// When we have a known good value for the 3x3 set of possible values
	// this function sets it and ensures that all of the other values are
	// zeroed out so that we no longer worry about them
	void SetValidValuesBlock(int i, int j, int value)
	{
		int row = i * 3;
		int col = j * 3;
		for (int ii = 0; ii < 3; ii++)
		{
			for (int jj = 0; jj < 3; jj++)
			{
				if (validValues[row + ii][col + jj] != value)
					validValues[row + ii][col + jj] = 0;
			}
		}
	}

	// IF there is only one value in the 3x3 grid of valid values
	// AND the solution values table has a zero in this location
	// we have a number we can plug back into the solution values table
	int GetValidValuesBlock(int i, int j)
	{
		int row = i * 3;
		int col = j * 3;
		int numFound = 0;
		int validValue = 0;
		for (int ii = 0; ii < 3; ii++)
		{
			for (int jj = 0; jj < 3; jj++)
			{
				if (validValues[row + ii][col + jj])
				{
					validValue = validValues[row + ii][col + jj];
					numFound++;
					if (numFound > 1)
						return 0;
				}
			}
		}

		if (numFound == 1)
			return validValue;

		return 0;
	}

	// This function is used to get the valid value
	// from the valid values table for a given cell
	// at a certain row and column and certain value offset
	// Its used when backtracking because we don't to try 
	// every value from 1 to 9 while backtracking, ONLY
	// the values that appear in the valid value table
	int GetNextValidValue(int i, int j, int k)
	{
		int row = i * 3;
		int col = j * 3;
		int numFound = 0;
		for (int ii = 0; ii < 3; ii++)
		{
			for (int jj = 0; jj < 3; jj++)
			{
				if (validValues[row + ii][col + jj])
				{
					numFound++;
					if(numFound == k)
						return validValues[row + ii][col + jj];
				}
			}
		}

		return 0;
	}

	// This function looks at a given cell's entry in the valid
	// values table and returns the number of valid values in the table
	int ValidValuesCount(int i, int j)
	{
		int row = i * 3;
		int col = j * 3;
		int numFound = 0;
		for (int ii = 0; ii < 3; ii++)
		{
			for (int jj = 0; jj < 3; jj++)
			{
				if (validValues[row + ii][col + jj])
				{
					numFound++;
				}
			}
		}

		return numFound;
	}


	// This will remove the value passed in as valid value
	// for this block of valid values for the solution row, col given
	void MarkValueBlock(int i, int j, int value)
	{
		int row = (i * 3) + ((value - 1) / 3);
		int col = (j * 3) + ((value - 1) % 3);
		validValues[row][col] = 0;
	}

	// Put the puzzle known values into the solution
	// Mark the ValidValues blocks with the known values
	void Initialize(int currentPuzzle)
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (puzzleValues[currentPuzzle][i][j])
				{
					solutionValues[i][j] = puzzleValues[currentPuzzle][i][j];
					SetValidValuesBlock(i, j, puzzleValues[currentPuzzle][i][j]);
				}
			}
		}
	}

	// This removes the single number from valid values block
	// that is in this solution row for each col in that row
	void SolutionMarkRows()
	{
		for (int row = 0; row < 9; row++)
		{
			for (int col = 0; col < 9; col++)
			{
				if (solutionValues[row][col])
				{
					for (int localCol = 0; localCol < 9; localCol++)
					{
						if (col != localCol)
							MarkValueBlock(row, localCol, solutionValues[row][col]);
					}
				}
			}
		}
	}

	// This removes the single number from the valid values block
	// that is in this solution column for each row in that col
	void SolutionMarkColumns()
	{
		for (int col = 0; col < 9; col++)
		{
			for (int row = 0; row < 9; row++)
			{
				if (solutionValues[row][col])
				{
					for (int localRow = 0; localRow < 9; localRow++)
					{
						if (row != localRow)
							MarkValueBlock(localRow, col, solutionValues[row][col]);
					}
				}
			}
		}
	}

	// This removes the single number from valid values block
	// that is in the this solution 3x3 block 
	// for each row and col in that block
	void SolutionMarkBlocks()
	{
		for (int row = 0; row < 9; row++)
		{
			for (int col = 0; col < 9; col++)
			{
				if (solutionValues[row][col])
				{
					int blockRowStart = ((row / 3) * 3);
					int blockColStart = ((col / 3) * 3);
					for (int localRow = blockRowStart; localRow < blockRowStart + 3; localRow++)
					{
						for (int localCol = blockColStart; localCol < blockColStart + 3; localCol++)
						{
							if (row != localRow || col != localCol)
								MarkValueBlock(localRow, localCol, solutionValues[row][col]);
						}
					}
				}
			}
		}
	}

	// THis function will iterate over the solution table
	// Whenever it finds a zero, it will check the valid values table
	// and the valid values table contains a single number, we know
	// we have found a solution value which can be plugged back in
	// When this function returns zero and there are no more zeroes
	// in the solution table, the puzzle is solved.
	// When this function returns zero and there are still zeroes
	// in the solution table, we have to go to the next stage
	int ValidValuesPutBack()
	{
		int numFound = 0;

		for (int row = 0; row < 9; row++)
		{
			for (int col = 0; col < 9; col++)
			{
				if (solutionValues[row][col] == 0)
				{
					int solution = GetValidValuesBlock(row, col);
					if (solution)
					{
						solutionValues[row][col] = solution;
						numFound++;
						cout << "Solution value " << solution << " found for " << row << "," << col << "\n";
					}
				}
			}
		}

		return numFound;
	}

	// This function is going to grab all of the remaining valid values
	// in the 3x3 grid for the row/col passed in and see if any of those
	// values is unique for the super row of values this belongs to where
	// the super row is the row of 3x3 grids for the row passed in.
	int GetValidValuesSuperRow(int row, int col)
	{
		int localValidValues[9] = { 2,2,2,2,2,2,2,2,2 };

		int rowStart = row * 3;
		int colStart = col * 3;
		int currentValue = 0;
		for (int localRow = rowStart; localRow < rowStart + 3; localRow++)
		{
			for (int localCol = colStart; localCol < colStart + 3; localCol++)
			{
				if (!validValues[localRow][localCol])
					localValidValues[currentValue] = 0;
				currentValue++;
			}
		}

		for (int superRow = rowStart; superRow < (rowStart + 3); superRow++)
		{
			for (int superCol = 0; superCol < 27; superCol++)
			{
				if (validValues[superRow][superCol])
				{
					int index = validValues[superRow][superCol] - 1;
					if (localValidValues[index])
						localValidValues[index]--;
				}
			}
		}

		int validValuesCount = 0;
		int result = 0;
		for (int i = 0; i < 9; i++)
		{
			if (localValidValues[i])
			{
				if (!validValuesCount)
				{
					result = i+1;
					validValuesCount++;
				}
				else
				{
					result = 0;
					validValuesCount++;
				}
			}
		}

		return result;
	}

	// This function is going to grab all of the remaining valid values
	// in the 3x3 grid for the row/col passed in and see if any of those
	// values is unique for the super col of values this belongs to where
	// the super col is the col of 3x3 grids for the row passed in.
	int GetValidValuesSuperCol(int row, int col)
	{
		int localValidValues[9] = { 2,2,2,2,2,2,2,2,2 };

		int rowStart = row * 3;
		int colStart = col * 3;
		int currentValue = 0;
		for (int localRow = rowStart; localRow < rowStart + 3; localRow++)
		{
			for (int localCol = colStart; localCol < colStart + 3; localCol++)
			{
				if (!validValues[localRow][localCol])
					localValidValues[currentValue] = 0;
				currentValue++;
			}
		}

		for (int superCol = colStart; superCol < (colStart + 3); superCol++)
		{
			for (int superRow = 0; superRow < 27; superRow++)
			{
				if (validValues[superRow][superCol])
				{
					int index = validValues[superRow][superCol] - 1;
					if (localValidValues[index])
						localValidValues[index]--;
				}
			}
		}

		int validValuesCount = 0;
		int result = 0;
		for (int i = 0; i < 9; i++)
		{
			if (localValidValues[i])
			{
				if (!validValuesCount)
				{
					result = i + 1;
					validValuesCount++;
				}
				else
				{
					result = 0;
					validValuesCount++;
				}
			}
		}

		return result;
	}

	// This function is going to grab all of the remaining valid values
	// in the 3x3 grid for the row/col passed in and see if any of those
	// values is unique for the super block of values this belongs to where
	// the super block is the block of 3x3 grids for the cell passed in.
	int GetValidValuesSuperBlock(int row, int col)
	{
		int localValidValues[9] = { 2,2,2,2,2,2,2,2,2 };

		int rowStart = row * 3;
		int colStart = col * 3;
		int currentValue = 0;
		for (int localRow = rowStart; localRow < rowStart + 3; localRow++)
		{
			for (int localCol = colStart; localCol < colStart + 3; localCol++)
			{
				if (!validValues[localRow][localCol])
					localValidValues[currentValue] = 0;
				currentValue++;
			}
		}

		int blockRowStart = ((row / 3) * 9);
		int blockColStart = ((col / 3) * 9);
		for (int superRow = blockRowStart; superRow < blockRowStart + 9; superRow++)
		{
			for (int superCol = blockColStart; superCol < blockColStart + 9; superCol++)
			{
				if (validValues[superRow][superCol])
				{
					int index = validValues[superRow][superCol] - 1;
					if (localValidValues[index])
						localValidValues[index]--;
				}
			}
		}
		

		int validValuesCount = 0;
		int result = 0;
		for (int i = 0; i < 9; i++)
		{
			if (localValidValues[i])
			{
				if (!validValuesCount)
				{
					result = i + 1;
					validValuesCount++;
				}
				else
				{
					result = 0;
					validValuesCount++;
				}
			}
		}

		return result;
	}

	// This function will iterate over the solution table
	// Whenever it finds a zero, it will check the valid values table
	// super Row, super Col and super 3x3 Block for this cell and if
	// the valid values row, col or block contains a unique number, we know
	// we have found a solution value which can be plugged back in
	// When this function returns zero and there are no more zeroes
	// in the solution table, the puzzle is solved.
	// When this function returns zero and there are still zeroes
	// in the solution table, we need to re-iterate through
	// the first stage and pick up the new values and see if we are
	// fully filled out.
	int FindUniqueValidValues()
	{
		int numFound = 0;

		for (int row = 0; row < 9; row++)
		{
			for (int col = 0; col < 9; col++)
			{
				if (solutionValues[row][col] == 0)
				{
					int solution = GetValidValuesSuperRow(row, col);
					if (solution)
					{
						solutionValues[row][col] = solution;
						SetValidValuesBlock(row, col, solution);
						cout << "SuperRow Solution value " << solution << " found for " << row << "," << col << "\n";
						numFound++;
						continue;
					}
					
					solution = GetValidValuesSuperCol(row, col);
					if (solution)
					{
						solutionValues[row][col] = solution;
						SetValidValuesBlock(row, col, solution);
						cout << "SuperCol Solution value " << solution << " found for " << row << "," << col << "\n";
						numFound++;
						continue;
					}

					solution = GetValidValuesSuperBlock(row, col);
					if (solution)
					{
						solutionValues[row][col] = solution;
						SetValidValuesBlock(row, col, solution);
						cout << "SuperBlock Solution value " << solution << " found for " << row << "," << col << "\n";
						numFound++;
						continue;
					}
				}
			}
		}

		return numFound;
	}

	// Checks to see if the number passed in is already in a given row
	bool UsedInRow(int row, int num)
	{
	    for (int col = 0; col < 9; col++)
	        if (solutionValues[row][col] == num)
	            return true;
	    return false;
	}
 
 	// Checks to see if the number passed in is already in a given col
	bool UsedInCol(int col, int num)
	{
	    for (int row = 0; row < 9; row++)
	        if (solutionValues[row][col] == num)
	            return true;
	    return false;
	}
 
 	// Checks to see if the number passed in is already in a given 3x3 box
	bool UsedInBox(int boxStartRow, int boxStartCol, int num)
	{
	    for (int row = 0; row < 3; row++)
	        for (int col = 0; col < 3; col++)
	            if (solutionValues[row+boxStartRow][col+boxStartCol] == num)
	                return true;
	    return false;
	}
 
 	// Checks to see if putting the num passed in into position row, col
 	// will render the puzzle solution we are building invalid.
	bool IsPuzzleOkay(int row, int col, int num)
	{
	    return !UsedInRow(row, num) &&
	           !UsedInCol(col, num) &&
	           !UsedInBox(row - row%3 , col - col%3, num);
	}

	// This finds the first row, col entry that has a zero in it
	// If it returns false, the puzzle is solved
	bool FindUnassignedRowCol(int &row, int &col)
	{
		for (row = 0; row < 9; row++)
		{
			for (col = 0; col < 9; col++)
			{
				if (solutionValues[row][col] == 0)
					return true;
			}
		}

		return false;		
	}

	// Iterate across the solution
	// and for each cell that is zero, assign a "guess"
	// from the valid values table and check if that is okay.
	// if not, back track until they all are!
	bool Backtrack()
	{
		// This will be called recursively
		//
		// We will start at the top left and go row by row
		// looking for entries that are still zeroes.
		// When we find one, we will look at the cell's entry
		// in the valid values table and pick the next available valid value.
		// 
		// After we set the cell to that value, we then check the puzzle
		// to see if its valid.  If it is, we move on to the next value.
		// If not, we try the next higher value in the valid values table
		// If we run out of valid values, we backtrack to the previous cell
		// and try its next value.  And so on until we place a value in the
		// last open cell and the puzzle checks as valid.
		//
		// We should ONLY need to check the row, col and 3x3 of the new value
		// that we put in.  No other row, col or 3x3 could have been made invalid.
		//

		// Let's find the first open cell row, col.
		// if we get back false, puzzle should be solved!
		int row = 0, col = 0;
		if(!FindUnassignedRowCol(row, col))
			return true;

		// Iterate through all of the valid values we have left for this cell
		// This is the magic of the valid values table. Instead of having to 
		// backtrack all numbers from 1 to 9, we only neex to check the valid
		// remaining vqlues.
		int numValidValues = ValidValuesCount(row, col);
		for(int i=1; i<=numValidValues; i++)
		{
			// Pull this row, col entries from the valid values table
			int validValue = GetNextValidValue(row, col, i);

			// If this value doesn't invalidate the puzzle, 
			// recurse into the next available cell
			if(IsPuzzleOkay(row, col, validValue))
			{
				solutionValues[row][col] = validValue;

				if(Backtrack())
					return true;

				solutionValues[row][col] = 0;
			}
		}

		return false;
	}

	void WritePuzzle(int currentPuzzle)
	{
		cout << "Puzzle: " << currentPuzzle << "\n";
		for (int row = 0; row < 9; row++)
		{
			for (int col = 0; col < 9; col++)
			{
				cout << puzzleValues[currentPuzzle][row][col] << " ";
			}
			cout << "\n";
		}
	}

	void WriteSolution()
	{
		cout << "Solution:\n";
		for (int row = 0; row < 9; row++)
		{
			for (int col = 0; col < 9; col++)
			{
				cout << solutionValues[row][col] << " ";
			}
			cout << "\n";
		}
	}
	
	void WriteValidValues()
	{
		cout << "Valid Values:\n";
		for (int row = 0; row < 27; row++)
		{
			for (int col = 0; col < 27; col++)
			{
				cout << validValues[row][col] << " ";
			}
			cout << "\n";
		}
	}

	bool IsPuzzleSolved()
	{
		for (int row = 0; row < 9; row++)
		{
			for (int col = 0; col < 9; col++)
			{
				if (solutionValues[row][col] == 0)
					return false;
			}
		}

		return true;
	}
};

int main(int argc, char* argv[])
{
	SudokuSolver solution;
	int currentPuzzle = 0;
	while(currentPuzzle < 8)
	{
		solution.Reset();
		solution.Initialize(currentPuzzle);

		solution.WritePuzzle(currentPuzzle);

		int passes = 0;
		int numFound = 0;
		// 1st Stage
		// Use the fact that each row, col and 3x3 block
		// in the puzzle can only have the numbers 1 through 9
		// in them.  This will solve easy to medium puzzles.
		// For less determined puzzles, we go to stage two.
		do
		{
			numFound = 0;
			int totalFound = 0;
			do
			{
				solution.SolutionMarkRows();
				solution.SolutionMarkColumns();
				solution.SolutionMarkBlocks();
				totalFound = solution.ValidValuesPutBack();
				numFound += totalFound;
			} while (totalFound);

			// 2nd Stage
			// For some puzzles the above will be enough to generate
			// a solution.  For less determined puzzles, we need to
			// use the additional fact that each row, col and 3x3 block
			// must have each of the numbers 1 through 9 in them.  We
			// do this by checking the valid values table 3x rows, cols
			// and blocks that correspond to each solution cell and
			// looking for unique values for that location. If we 
			// find one, we know that we have the answer.
			if (!solution.IsPuzzleSolved())
			{
				numFound += solution.FindUniqueValidValues();
			}

			passes++;
			cout << "Completed Pass " << passes << "\n";
		}
		while ((numFound) && !solution.IsPuzzleSolved());

		if (!solution.IsPuzzleSolved())
		{
			// If we get here, the puzzle doesn't have enough numbers
			// to find a solution without guessing.
			// So we need to backtrack to fill in the remaining numbers
			// Theoretically, this should be pretty fast since a large number
			// of the values have hopefully already been found!
			// The really good news is that we can "Smart Backtrack(tm)"
			// Why?  Well our Valid Values grid knows that the undefined cells
			// have only a small set of possible numbers that they have to be!
			// So, when we backtrack, we only have to try those values!  Not all 10!
			solution.WriteValidValues();

			cout << "Backtracking with Valid Values to solve:\n";
			solution.Backtrack();
		}

		solution.WriteSolution();
		currentPuzzle++;
	}

	return 0;
}

