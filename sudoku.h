#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

/**
This function checks each slot in the grid if a number is
inputted, it returns true if there is no number and false otherwise
**/
bool chkNoNum(int puzzle[9][9], int &row, int &col);

/**
This functions checks if a number is safe to be inputted to a slot
based on whether the number exists in the same row, column, and box.
**/
bool chkIfSafe(int puzzle[9][9], int row, int col, int num);

/**
This function is used to check if the sudoku puzzle entered is valid
by checking if the predetermined numbers conflict with the row, column, and box.
**/
bool chkIfUsed(int puzzle[9][9], int row, int col, int num);

/**
This is the main function that calls all other functions to solve the puzzle
by recursively trying possible numbers by using the chkIfSafe function
**/
bool solveSudoku(int puzzle[9][9])
{
	int row, col; //The current row and column index being checked

	if(!chkNoNum(puzzle, row, col)) //Checking for any unassigned slots.
  {
    return true; //If there are no unassigned slots then the puzzle is done.
  }

	for(int num = 1; num <= 9; num++) //Check all possible numbers
	{
		if(chkIfSafe(puzzle, row, col, num))
		{
			puzzle[row][col] = num; //Assigns a candidate

			if(solveSudoku(puzzle)) //Recursive call
      {
				return true;
      }
      else
      {
        puzzle[row][col] = 0; //Not valid
      }
		}
	}
	return false; //False to trigger backtracking
}

///Function checks if puzzle is solvable in the first place as said above
bool chkSudoku(int puzzle[9][9])
{
  int row, col;
  for(row = 0; row < 9; row++)//Check rows
  {
    for(col = 0; col < 9; col++)//Check columns
    {
      if(puzzle[row][col] != 0)//Check for assigned values (i.e. Not 0)
      {
        if(!chkIfUsed(puzzle, row, col, puzzle[row][col]))//Checks if assigned num is used already
        {
          cout << "\nERROR: Problem at Row " << row + 1
          << " x Column " << col + 1 << " with number " << puzzle[row][col] << endl;
          return false;//Return false if there is a duplicate number and outputs problem location
        }
      }
    }
  }
  return true;//Returns true if puzzle is valid
}

///Function that checks for an unassigned slot
bool chkNoNum(int puzzle[9][9], int &row, int &col)
{
	for(row = 0; row < 9; row++)
  {
		for(col = 0; col < 9; col++)
		{
			if(puzzle[row][col] == 0)
      {
				return true;//True if a slot is unassigned
      }
		}
  }
	return false;//False if all slots are assigned
}

///Checks the row for a number specified and returns true if the number is found
bool chkRow(int puzzle[9][9], int row, int num)
{
	for(int col = 0; col < 9; col++)
  {
		if(puzzle[row][col] == num)
    {
			return true;
    }
  }
	return false;
}

///Checks the column for a number specified and returns true if the number is found
bool chkCol(int puzzle[9][9], int col, int num)
{
	for(int row = 0; row < 9; row++)
  {
		if(puzzle[row][col] == num)
    {
			return true;
    }
  }
	return false;
}

///Checks the box or smaller 3x3 grid for a duplicate number
bool chkBox(int puzzle[9][9], int startRow, int startCol, int num)
{//startRow and startCol are the upper left corners of the sub-grid
	for(int row = 0; row < 3; row++)
  {
		for(int col = 0; col < 3; col++)
    {
			if(puzzle[row + startRow][col + startCol] == num)
      {
				return true;
      }
    }
  }
	return false;
}

/**
The function that uses the three previous functions to check if
a number can safely be placed is a slot. Returns true if no duplicate
number is found in the box, row, and column.
**/
bool chkIfSafe(int puzzle[9][9], int row, int col, int num)
{
	return !chkBox(puzzle, row - row%3 , col - col%3, num)
         && !chkRow(puzzle, row, num)
         && !chkCol(puzzle, col, num);
}

/**
This function is a sort of opposite to chkIfSafe but returns
true if a number has no duplicate in the col, row, and box.

New code had to be written for this because the above code will consider
the slot that is currently being checked. So if we check if 8 is used in
[0][1] or 1x2, using the functions above, it will always return that the
number exists because 8 exists in that current slot.
**/
bool chkIfUsed(int puzzle[9][9], int row, int col, int num)
{
  bool ckRow = false, ckCol = false, ckBox = false; //Boolean variables for Row, Col, and Box

  for(int tcol = 0; tcol < 9; tcol++) //Chk Row
  {
		if(puzzle[row][tcol] == num)
    {
      if(tcol != col)///The important part that is needed for this function to work
      {
        ckRow = true;//True meaning a duplicate was found
      }
    }
  }

  for(int trow = 0; trow < 9; trow++) //Chk Col
  {
		if(puzzle[trow][col] == num)
    {
      if(trow != row)
      {
        ckCol = true;
      }
    }
  }

  //These integers are the upper left corner of the sub-boxes or 3x3 grids
  int startRow = row - row%3;
  int startCol = col - col%3;
  for(int trow = 0; trow < 3; trow++) //Chk Box
  {
		for(int tcol = 0; tcol < 3; tcol++)
    {
			if(puzzle[trow + startRow][tcol + startCol] == num)
      {
        if(trow + startRow != row && tcol + startCol != col)
        {
          ckBox = true;
        }
      }
    }
  }

  if(!ckBox && !ckCol && !ckRow)
  {//Return true if no matches are found
    return true;
  }
  else
  {//Return false otherwise
    return false;
  }
}

///Function to print the puzzle
void printPuzzle(int puzzle[9][9])
{
  //cout << "\nPUZZLE:\n";
  cout << "||===|===|===||"
           << "===|===|===||"
           << "===|===|===||\n";
  for(int row = 0; row < 9; row++)
  {
    cout << "|";
    for(int col = 0; col < 9; col++)
    {
      if(col % 3 == 0 && col != 0)
      {
        cout << "|";
      }
      cout << "| " << puzzle[row][col] << " ";
      if(col == 8)
      {
        cout << "||";
      }
    }
    if(row == 2 || row == 5)
    {
      cout << "\n||===|===|===||===|===|===||===|===|===||";
    }
    else
    {
      cout << "\n||---|---|---||---|---|---||---|---|---||";
    }
    cout << endl;
  }
  cout << "||===|===|===||"
         << "===|===|===||"
         << "===|===|===||\n";

}

///Function that reads a puzzle from a text file using fstream
bool readPuzzle(int puzzle[9][9], string filename)
{
  cout << "Reading from file: " << filename << endl;
  ifstream fin(filename);//ifstream declaration

  //In the case that a file with 'filename' isn't found
  if(!fin)
  {
    cout << "No file with filename '" << filename << "' found.\n";
    return false;
  }

  //The main code that read from a file
  else
  {
    cout << "File: " << filename << " found.\n\n";
    string input;
    int in;
    for(int row = 0; row < 9; row++)//Row for loop
    {
      getline(fin, input);//Gets a line for each row
      stringstream ss(input);//Passes the line to a string stream
      for(int col = 0; col < 9; col++)//Column for loop
      {
        if(ss >> in)//If an integer is successfully inserted
        {
          if(in > 9)
          {
            cout << "ERROR: Integer in " << row + 1 << "x" << col + 1
            << " in puzzle entered is greater than 9.\n";
            return false;
          }
          else
          {
            puzzle[row][col] = in; //Assigning the integer to the grid
          }
        }
        else//In case an integer is not passed signifying a blank or unassigned slot
        {   //This is necessary to continue reading from the file otherwise when an int
            //is not successfully inserted the rest of the grid won't be read.
          ss.clear();
          string trash;
          ss >> trash;
          puzzle[row][col] = 0; //The grid is assigned to 0 or an unassigned slot.
        }
      }
    }
    return true;//True if a file with 'filename' is successfully read
  }
  return false;//False if no file is found
}

///Function to output the solution to a text file if a user wishes so
void printFile(int puzzle[9][9])
{
  fstream output; //Declaring an fstream
  output.open("solved.txt", std::fstream::out); //Saving a new file named "solved.txt"

  for(int row = 0; row < 9; row++)
  {
    for(int col = 0; col < 9; col++)
    {
      output << puzzle[row][col] << " ";
    }
    output << endl;//Endline after each row
  }

  output.close();//Closing and saving the file
}

