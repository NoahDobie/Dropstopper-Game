Dropstopper!!

This is a simple console-based game where numbers fall from the top of the screen, and the player must press the matching number on the keyboard before it hits the bottom of the screen. The game has different difficulty levels based on the player's score.

It's really simple and straightforward, just download and play!

Extract zip file, and put folder in a good location

Best to play using the .exe file as using in console doesn't work great (designed for windows cmd)

Folder is needed to keep track of highscores as a textfile is created!

Actual code/game description:

This code is a simple game called "Dropstopper", where the player must press the number on the keyboard that matches the number that is falling on the screen before it reaches the bottom. The gameboard is represented by a 2D array of characters, and the game's state is stored in various variables such as score, lives, ypos, and randomNum. The code uses the Windows API function "system()" to set the console mode, clear the screen, and change the console title. The game's main loop is implemented using a while loop, and the game's speed increases as the player's score increases. The code also uses the C library function "srand()" to seed the random number generator, and the "clock()" function to control the timing of the game's updates.

The gameboard is a 2D char array of size ROWS x COLUMNS and is initialized to 0.

The variables score, lives, ypos, randomNum, objects, print, and delay are used to store the player's score, remaining lives, the current y-position of an object, a randomly generated number, the number of objects currently on the board, a flag for printing the board, and the speed of the game.

The function run() is called in the main function and handles the majority of the game logic such as setting the board, spawning random objects, checking for game over, and updating the board.

The function RandomObjectSpawn() randomly generates a number and places it on the top of the board.

The function GameOver() is called when the player loses all their lives and displays a game over message.

The function CheckBottom() checks if an object has reached the bottom of the board, and if it has, the player loses a life.

The function ObjectDrop(int x) is used to move the object on the board downwards.

The function KeyPressed(char c) checks if the player pressed the correct key and updates the score accordingly.


