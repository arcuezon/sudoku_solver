#include "sudoku.h"
#include <cstdio>

using namespace std;

int main()
{
	int puzzle[9][9]; //Declaring the array where the puzzle will be stored
	string filename; //Filename string variable

	//Prompt to user to input filename of the puzzle
	cout << "Enter filename of puzzle: ";
	cin >> filename;

	//Calling the function to read from file
	if(!readPuzzle(puzzle, filename))
  {
    system("pause");
    return 1;//If a file isn't found the program exists and returns 1.
  }

  //Printing the unsolved puzzle
	cout << "Unsolved Puzzle:\n";
	printPuzzle(puzzle);

	//Checks if the entered puzzle is valid in the first place
	if(!chkSudoku(puzzle))
  {
    system("pause");
    return 1;//Exits and returns 1 if puzzle is invalid
  }

  ///Calls the main function to solve the puzzle
	if (solveSudoku(puzzle) == true)
  {//If a solution is found, the solved puzzle will be outputted
    cout << "\nSolved Puzzle:\n";
		printPuzzle(puzzle);

		///Asking the user if a copy of the solved puzzle should be saved to a text file
		char save;
		cout << "\nWould you like to save the solved puzzle to a text file(Y/N)? ";
		cin >> save;

    if(save == 'N')//No copy will be saved
    {
      system("pause");
      return 0;
    }
    else if(save == 'Y')//Save a copy
    {
      cout << "\nSaving solved puzzle to a text file with filename: 'solved.txt'.\n";
      printFile(puzzle); //Calling the printFile function
    }
    else
    {
      cout << "\nERROR: Invalid command entered. Exiting program...\n";
      system("pause");
      return 0;
    }
  }
	else
  {//In case no solution is found
    cout << "\nNo solution found.\n";
  }

  system("pause");
	return 0;
}
