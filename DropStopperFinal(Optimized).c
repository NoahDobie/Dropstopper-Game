#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <conio.h>
#include <windows.h>

#define ROWS 20
#define COLUMNS 30
#define TRUE 1
#define FALSE 0

char gameboard[ROWS][COLUMNS] = {0};

int score = 0, lives = 0, ypos = 0, randomNum = 0, objects = 1, print = 1, delay = 51;

char ch;

double TIME_TO_WAIT, speed;
char GAMEON = TRUE;

void run();
void SetBoard();
void PrintBoard();
void RandomObjectSpawn();
void GameOver();
void CheckBottom();
void ObjectDrop(int x);
void KeyPressed(char c);

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

void run() {

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

	SetBoard();
	PrintBoard();

	clock_t last = clock();
	while(GAMEON) {
    clock_t current = clock();

		if (score < 15) {
			TIME_TO_WAIT = 1.0;
			speed = 1;
		}
		else if (score < 30) {
			TIME_TO_WAIT = .75;
			speed = 1.5;
			system("color 3");
		}
		else if (score < 50) {
			TIME_TO_WAIT = .5;
			speed = 2;
			system("color 2");
		}
		else if (score >= 50) {
			TIME_TO_WAIT = .4;
			speed = 2.5;
			system("color 5");
		}
		else if (score >= 100) {
			TIME_TO_WAIT = .3;
			speed = 3;
			system("color 8");
		}
    	if (current >= (last + TIME_TO_WAIT * CLOCKS_PER_SEC)) {
        	
			int top;

			if (score <= 80) {
				if (print == TRUE) {
					RandomObjectSpawn();
					top = 1;
					print = FALSE; //print every second object drop
			}	
				else {
					top = 0;
					print = TRUE;
				}
			}
			else {
				top = 0;
				RandomObjectSpawn();
			}
			CheckBottom();
			ObjectDrop(top);
			PrintBoard();
			last = current;
    	}
		if (_kbhit()) {
				ch = _getch();
				KeyPressed(ch);
			}
	}
}

void SetBoard() {

	int i, j;

	for(i = 0; i < ROWS ; i++){
		for(j = 0; j < COLUMNS ; j++){
			if (i == 19) {
				gameboard[i][j] = '=';
				//printf("%s", &gameboard[i][j]);
			}
			else if (j == 0) {
				gameboard[i][j] = '|';
				//printf("%s", &gameboard[i][j]);
			}
			else if (j == 29) {
				gameboard[i][j] = '|';
				//printf("%s\n", &gameboard[i][j]);
			}
			else {
				gameboard[i][j] = ' ';
				//printf("%s", &gameboard[i][j]);
			}
		}
	}
}

void PrintBoard() {
	
	system("cls");
	int i, j;
	for(i = 0; i < ROWS ; i++) {
		for(j = 0; j < COLUMNS ; j++){
			printf("%c", gameboard[i][j]);
		}
		printf("\n");
	}

	printf("\nLives Remaining: %d", lives);
	printf("\nScore = %d\n", score);
	printf("\nSpeed = %0.1fX\n", speed);
		
}

void RandomObjectSpawn() {

	ypos = rand() % 28 + 1; //number from 1 to 29 for x pos between grid pattern
	randomNum = rand() % ((57+1)-48) + 48;; //to get ASCII values from 0 to 9 for keyboard inputs (0 to 9 ASCII = 48 to 57 dec)
	gameboard[0][ypos] = randomNum;
}

void ObjectDrop(int x) {

	int i, j;

	for (i = 17; i >= x; --i) {
		for (j = 1; j < COLUMNS-1; j++) {
			char temp;
  			temp = gameboard[i][j];
  			gameboard[i][j] = gameboard[i+1][j];
  			gameboard[i+1][j] = temp;
		}
	}
}

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

	int i, j, stop;

	for (i = 18; i >= 0; i--) {

		if (stop < 1) {

			for (j = 1; j < COLUMNS-1; j++){ //only read on inside columns to speed up process and optimize
			
				if (gameboard[i][j] == c) {
					gameboard[i][j] = ' ';
					++score;
					stop = 1;
					PrintBoard();
				}
				else {
					ch = '\0';
				}
			
				}
		}
		else {
			break;
		}
	}	
}

void GameOver() {
	if (lives <= 0) {
		GAMEON = FALSE; //stop main loop until user presses play again options
		system("cls");

		printf("\n          GAME OVER!\n");
		printf("\nYou earned a score of: %d!\n", score);

		FILE* fp;
		fp = fopen("topscore.txt","a+"); //open for read and write, but no changing / create if not there yet
		
		int i = 0;
		int tempscore = 0;
 
  		while (!feof (fp)){  
      		fscanf (fp, "%d", &i);   
			tempscore = i;
				break;
    	}
		fclose(fp); //close before determining if needed to write

		if (tempscore < score) {
				fp = fopen("topscore.txt","w+"); //open to write and override file
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


