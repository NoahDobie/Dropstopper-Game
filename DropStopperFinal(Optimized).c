//created by noah dobie

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <conio.h>
#include <windows.h>

#define ROWS 20  // Number of rows in the game board
#define COLUMNS 30  // Number of columns in the game board
#define TRUE 1
#define FALSE 0

char gameboard[ROWS][COLUMNS] = {0}; // Initialize the game board with all elements set to 0

// Variable initialization
int score = 0, lives = 0, ypos = 0, randomNum = 0, objects = 1, print = 1, delay = 51;

char ch;

double TIME_TO_WAIT, speed;
char GAMEON = TRUE;

// Method/function declaration
void run();
void SetBoard();
void PrintBoard();
void RandomObjectSpawn();
void GameOver();
void CheckBottom();
void ObjectDrop(int x);
void KeyPressed(char c);

// Main function to setup console and begin the game!
int main() {
	srand(time(NULL));

	system("MODE 30,26");
	SetConsoleTitle("Drop Stopper - by Noah Dobie");

	system("cls");
	printf("   Welcome to Drop Stopper!\n\n  The numbers will fall from\n  the top, and you must press\n  the matching number on the\n  keyboard before it hits the\n     bottom of the board!\n\n          Good Luck!\n\n");
	system("pause");
	
	char pA = 'y';
	while ((pA == 'y') | (pA == 'Y')) {
		system("color 4");
		SetBoard();
		run();
    	printf("\nWant to play again? (Y/N): ");
    	scanf(" %c", &pA);
		GAMEON = TRUE;
	}
	return (0);
}

// Function for the main game loop
void run() {

	// Function calls to set up the game board, print the board, and spawn random objects
	score = 0;
	speed = 1;
	lives = 5;
	ypos = 0;
	randomNum = 0;
	objects = 1;
	print = 1;
	TIME_TO_WAIT = 1.0;
	delay = 51;

	gameboard[9][9] = 'S'; gameboard[9][10] = 'T'; gameboard[9][11] = 'A'; gameboard[9][12] = 'R'; gameboard[9][13] = 'T'; gameboard[9][14] = 'I'; gameboard[9][15] = 'N'; gameboard[9][16] = 'G';
	gameboard[9][17] = ' '; gameboard[9][18] = 'I'; gameboard[9][19] = 'N'; 
	clock_t last2 = clock();
	while(delay > 47) {
    clock_t current2 = clock();
    	if (current2 >= (last2 + TIME_TO_WAIT * CLOCKS_PER_SEC)) {
			gameboard[11][14] = delay;
			PrintBoard();
			last2 = current2;
			delay--;
		}
	}

	// Function to set up the game board
	SetBoard();
	// Function to print the game board
	PrintBoard();

	// Determine the time to wait and speed based on the score
	clock_t last = clock(); // Initialize last variable as current time
	while(GAMEON) {
    clock_t current = clock(); // Current time

		if (score < 15) {
			TIME_TO_WAIT = 1.0;
			speed = 1;
		}
		else if (score < 30) {
			TIME_TO_WAIT = .75;
			speed = 1.5;
			system("color 3"); // Change the color of the console
		}
		else if (score < 50) {
			TIME_TO_WAIT = .5;
			speed = 2;
			system("color 2"); // Change the color of the console
		}
		else if (score >= 50) {
			TIME_TO_WAIT = .4;
			speed = 2.5;
			system("color 5"); // Change the color of the console
		}
		else if (score >= 100) {
			TIME_TO_WAIT = .3;
			speed = 3;
			system("color 8"); // Change the color of the console
		}
		// If the current time is greater than or equal to the last time plus the time to wait
    	if (current >= (last + TIME_TO_WAIT * CLOCKS_PER_SEC)) {
        	
			int top;

			// If the score is less than or equal to 80, alternate between spawning an object and not spawning one
			if (score <= 80) {
				if (print == TRUE) {
					RandomObjectSpawn();
					top = 1;
					print = FALSE; // Print every second object drop
			}	
				else {
					top = 0;
					print = TRUE;
				}
			}
			// If the score is greater than 80, spawn an object every time
			else {
				top = 0;
				RandomObjectSpawn();
			}
			// Check if any number has hit the bottom
			CheckBottom();
			// Drop a number from the top
			ObjectDrop(top);
			// Print the game board
			PrintBoard();
			// Update the last time
			last = current;
    	}
		// If a key is pressed
		if (_kbhit()) {
				ch = _getch(); // Store the key
				KeyPressed(ch); // Call key pressed function
			}
	}
}

void SetBoard() {

	// Initialize variables for looping through the gameboard
	int i, j;

	// Loop through the rows and columns of the gameboard
	for(i = 0; i < ROWS ; i++){
		for(j = 0; j < COLUMNS ; j++){
			// If the current row is the last row, set the character to '='
			if (i == 19) {
				gameboard[i][j] = '=';
				//printf("%s", &gameboard[i][j]);
			}
			// If the current row is the last row, set the character to '|'
			else if (j == 0) {
				gameboard[i][j] = '|';
				//printf("%s", &gameboard[i][j]);
			}
			// If the current row is the last row, set the character to '|'
			else if (j == 29) {
				gameboard[i][j] = '|';
				//printf("%s\n", &gameboard[i][j]);
			}
			// If the current row is the last row, set the character to ' '
			else {
				gameboard[i][j] = ' ';
				//printf("%s", &gameboard[i][j]);
			}
		}
	}
}

void PrintBoard() {
	
	// Clear the console
	system("cls");
	// Initialize the variables
	int i, j;
	// Loop through rows and columns to print each
	for(i = 0; i < ROWS ; i++) {
		for(j = 0; j < COLUMNS ; j++){
			printf("%c", gameboard[i][j]);
		}
		printf("\n");
	}

	// Print lives, score, and speed at the bottom after the board
	printf("\nLives Remaining: %d", lives);
	printf("\nScore = %d\n", score);
	printf("\nSpeed = %0.1fX\n", speed);
		
}

void RandomObjectSpawn() {

	ypos = rand() % 28 + 1; // Number from 1 to 29 for x pos between grid pattern
	randomNum = rand() % ((57+1)-48) + 48;; // To get ASCII values from 0 to 9 for keyboard inputs (0 to 9 ASCII = 48 to 57 dec)
	gameboard[0][ypos] = randomNum;

}

// Function to drop the numbers
void ObjectDrop(int x) {

	// Initialize variables
	int i, j;

	// Loop through the columns to move the objects all down
	for (i = 17; i >= x; --i) {
		for (j = 1; j < COLUMNS-1; j++) {
			char temp;
  			temp = gameboard[i][j];
  			gameboard[i][j] = gameboard[i+1][j];
  			gameboard[i+1][j] = temp;
		}
	}
}

// Function to check if any number has made it to the bottom without being pressed
void CheckBottom() {

	int i;
	for (i = 1; i < COLUMNS-1; i++) {
		if (gameboard[18][i] != ' ') {
			--lives;
			gameboard[18][i] = ' ';
			GameOver();
		} 
	}
}

void KeyPressed(char c) {

	// Loop through each row starting from the bottom
	int i, j, stop;

	for (i = 18; i >= 0; i--) {

		if (stop < 1) { // Check if it must stop

			// Loop through each column, starting from the second column and ending at the second to last column
			for (j = 1; j < COLUMNS-1; j++){ // Only read on inside columns to speed up process and optimize
			
				if (gameboard[i][j] == c) { // If the current element on the gameboard is equal to the input character
					gameboard[i][j] = ' '; // Replace it with a blank space
					++score;
					stop = 1; //Set to 1 to exit the loop
					PrintBoard(); // Print the updated board
				}
				else {
					ch = '\0'; // If the current element is not equal to the input character, set ch to null
				}
			
				}
		}
		else {
			break; // Exit the loop if stop is equal to 1
		}
	}	
}

void GameOver() {
	if (lives <= 0) {
		GAMEON = FALSE; // Stop main loop until user presses play again options
		system("cls");

		printf("\n          GAME OVER!\n");
		printf("\nYou earned a score of: %d!\n", score);

		FILE* fp;
		fp = fopen("topscore.txt","a+"); // Open for read and write, but no changing / create if not there yet
		
		int i = 0;
		int tempscore = 0;
 
  		while (!feof (fp)){  
      		fscanf (fp, "%d", &i);   
			tempscore = i;
				break;
    	}
		fclose(fp); // Close before determining if needed to write

		if (tempscore < score) {
				fp = fopen("topscore.txt","w+"); //Open to write and override file
				fprintf(fp, "%d", score);
				printf("\nYou got the new highscore!\n\n");
			}
		else{
				printf("\nTry again to beat\nthe highscore of: %d\n\n", tempscore);
			}
		fclose(fp);
		system("pause");
	}
}


