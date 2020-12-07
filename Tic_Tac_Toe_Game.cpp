#include <iostream>
#include <string>

using namespace std;

void print_grid(string grid_array[4][4], int ARRAY_LENGTH)
{
	for (int i = 0; i < ARRAY_LENGTH; i++)
	{
		for (int j = 0; j < ARRAY_LENGTH; j++)
		{

			if (j == 3) {
				cout << grid_array[i][j] << endl;
				cout << "" << endl;
				//Prints Variable and line (leftmost edge)
			}
			else
			{
				cout << grid_array[i][j] << "\t";
				//Prints variable and space between
			}

		}
		//Goes through each column
	}
	//Goes through each row
	cout << endl;
}

string determine_turn(string grid_array[4][4], int ARRAY_LENGTH) {
	int X_count = 0;
	int O_count = 0;
	//Counts how many X's and O's have been placed in grid

	for (int x_index = 0; x_index < ARRAY_LENGTH; x_index++) {
		for (int y_index = 0; y_index < ARRAY_LENGTH; y_index++) {
			if (grid_array[x_index][y_index] == "X") {
				X_count++;
			}
			if (grid_array[x_index][y_index] == "O") {
				O_count++;
			}
		}
		//Goes through each element and increases X_count and O_count accordingly
	}
	if (X_count == O_count) {
		return "X";
		//Because X goes first, whenever they have the same amount it would be his turn
	}
	else {
		return "O";
		//And if not X's turn then its O's
	}
}

string determine_outcome(string grid_array[4][4], int ARRAY_LENGTH)
{
	int filled_spaces = 0;
	//This will determine if the game has ended by filling all the squares

	for (int x_index = 0; x_index < ARRAY_LENGTH; x_index++)
	{
		bool row_is_complete = true;
		bool column_is_complete = true;
		//This will keep track of whether the xth row and column is complete

		for (int y_index = 0; y_index < ARRAY_LENGTH; y_index++) {
			row_is_complete = row_is_complete && grid_array[x_index][0] == grid_array[x_index][y_index];
			column_is_complete = column_is_complete && grid_array[0][x_index] == grid_array[y_index][x_index];

			if (grid_array[x_index][y_index] == "X" || grid_array[x_index][y_index] == "O") {
				filled_spaces++;
			}
			//This if loop keeps tracks of the amount of blocks filled. Put in this for loop to save computing time by not having to relook through each block
		}
		//this for loop takes the initially set complete boolean, and checks whether a column is complete and at the same time if a row is complete

		if (row_is_complete || column_is_complete) {
			return grid_array[x_index][x_index];
			//This will return the winning player
			//Taking the string at x_index, x_index is guaranteed to be in either the winning row or column
		}
	}
	//x_index will be the column or row index
	//it will be kept constant while going through each value in that desired row or column

	bool diagonal1_complete = true;
	bool diagonal2_complete = true;
	//Similar idea, keeps track of whether the diagonal is complete
	for (int position_in_diagonal = 1; position_in_diagonal < ARRAY_LENGTH; position_in_diagonal++) {
		diagonal1_complete = diagonal1_complete && grid_array[0][0] == grid_array[position_in_diagonal][position_in_diagonal];
		diagonal2_complete = diagonal2_complete && grid_array[0][3] == grid_array[position_in_diagonal][3 - position_in_diagonal];
	}
	//Iterates though both diagonals at the same time

	if (diagonal1_complete) {
		return grid_array[0][0];
	}
	//If the 1st diagonal is complete return answer
	if (diagonal2_complete) {
		return grid_array[0][3];
	}
	//If the 2nd diagonal is complete return the answer

	if (filled_spaces == 16) {
		return "T";
	}

	return "N";
}


void input_number(string(&grid_array)[4][4], int ARRAY_LENGTH)
{

	//Declare and initialize variables
	string input_string;
	int user_input;

	//Getting the user to pick a number which corresponds to the location they want to take
	cout << "Pick a number on the grid to mark your location" << endl;
	cin >> user_input;
	cout << "" << endl;

	while (user_input <1 || user_input >16)
	{
		cout << "You have picked a number that does not exists on the board! Pick a number on the grid to mark your location" << endl;
		cin >> user_input;
		cout << "" << endl;
	}

	//Making the number they inputted into a string
	input_string = to_string(user_input);

	//Iterating through the for-loop to determine the location of the number the user inputted 
	for (int i = 0; i < ARRAY_LENGTH; i++)
	{
		for (int j = 0; j < ARRAY_LENGTH; j++)
		{
			//When the location of the number is found, the number gets replaced by an "x" or an "o" depending on whose turn it is
			if (grid_array[i][j] == input_string)
			{
				grid_array[i][j] = determine_turn(grid_array, ARRAY_LENGTH);

			}
		}
	}

	//Printing the updated array
	print_grid(grid_array, ARRAY_LENGTH);
}

void start_tic_tac_toe_simulation()
{
	/*
	* 1. Create The Grid
	* 2. Keep asking for input, and updating grid
	* 3. Keep checking if grid is complete
	* 4. Once grid is complete, return outcome
	*
	* functions:
	* check_complete_or_tie();
	* input_number();
	* determine_turn();
	* print_grid();
	*/
	const int ARRAY_LENGTH = 4;
	//Initialize constants

	int x_score = 0, o_score = 0;
	//Keep track of running scores

	int draws = 0;

	bool is_playing = true;
	//Used to keep the players playing or stop the program

	while (is_playing) {
		string grid_array[ARRAY_LENGTH][ARRAY_LENGTH] = { {"1","2","3","4"}, {"5","6","7","8"}, {"9","10","11","12"}, {"13","14","15","16"} };
		string go_again;
		//Setting up grid and play again variable for every game 

		print_grid(grid_array, ARRAY_LENGTH);
		//Prints grid

		while (determine_outcome(grid_array, ARRAY_LENGTH) == "N") {
			input_number(grid_array, ARRAY_LENGTH);
		} //Only works when outcome is "N" which means no outcome
		if (determine_outcome(grid_array, ARRAY_LENGTH) == "X") {
			cout << "X has won the game! Would you like to keep playing? (YES/NO)" << endl;
			x_score++;
		}
		else if (determine_outcome(grid_array, ARRAY_LENGTH) == "O") {
			cout << "O has won the game! Would you like to keep playing? (YES/NO)" << endl;
			o_score++;
		} //If someone wins print and increment their score and ask to go again
		else {
			cout << "The game has ended in a tie! Would you like to keep playing? (YES/NO)" << endl;
			draws++;
		} //If tie no score increase, but can choose to play again

		cin >> go_again;
		while (go_again != "YES" && go_again != "NO") {
			cout << "Invalid input, please input either \"YES\" or \"NO\"";
			cin >> go_again;
		}
		//Makes sure player inputs either yes or no in caps

		if (go_again != "YES") {
			is_playing = false;
		}
		//If we aren't playing then stop the loop 
		cout << endl << "Score: " << x_score << " (X) - " << o_score << " (O)" << endl << endl;
		//Give the final score
		cout << "Number of Draws: " << draws << endl << endl;
	}
}


int main()
{
	start_tic_tac_toe_simulation();
}
