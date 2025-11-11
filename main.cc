//Fill out this comment with your names and which bullet points you did
//Partners: Willems, Tran, Cook, Ugaz
//Bullet Points: Willems - Puzzles, Tran - Colors, Cook - Combat, Ugaz - World Map
//Extra Credit:
//URL to cover art and music:
#include "/public/read.h"
#include "/public/colors.h"
#include <vector>
#include <algorithm>
#include <unistd.h>
using namespace std;

//MAP FUNCTION DECLARATIONS


//Base for Level one only so far
vector<string> world_map = {
	"********************************",
	"* r                       |    *",
	"*  S                      | d  *",
	"*          S              |    *",
	"*                       x ---  *",
	"*     ---                    z *",
	"*     |B|                      *",
	"* S   | -- S                   *",
	"*   S |                    r   *",
	"*     ---                      *",
	"*                              *",
	"*                              *",
	"*                              *",
	"*                              *",
	"*------------------------------*", // This row should turn into ~~~~~~~~~~~~~~~~~~~~~~~ once the player picks up the blue shell (B for now), allowing them to now cross it
	"*                              *",
	"*                              *",
	"*                              *",
	"*                              *",
	"********************************"
};

char get_world_location(size_t row, size_t col) {
	if (row >= world_map.size()) return ' ';
	if (col >= world_map.at(row).size()) return ' ';
	return world_map.at(row).at(col);
}

void set_world_location(size_t row, size_t col, char c) {
	if (row >= world_map.size()) return;
	if (col >= world_map.at(row).size()) return;
	world_map.at(row).at(col) = c;
}

void print_world(size_t player_row, size_t player_col) {
	clearscreen();
	movecursor(0, 0);
	for (size_t row = 0; row < world_map.size(); row++) {
		for (size_t col = 0; col < world_map.at(row).size(); col++) {
			char c = world_map.at(row).at(col);
			if (row == player_row and col == player_col) cout << "@";
			else if (c == '*') cout << GREEN << c << RESET;
			else
				cout << c ;
		}
		cout << endl;
	}
}



int main() {

	//MAP STARTS HERE

	//*TODO Bunny Demo Code

	/*	cout << RED << "Hello World!\n" << RESET << "I am Reset.\n" << GREEN << "Welcome to the Farm!\n";
		cout << BOLDBLACK << "This is boldblack!\n";
		cout << BOLDGREEN << "This is boldgreen!\n";
		cout << RESET;
		setbgcolor(60,40,200);
		setcolor(200,40,60);
		cout << "Hit a number to continue\n";
		int temp;
		cin >> temp;
		set_cursor_mode(false);
		for (int i = 0; i < 255; i++) {
		clearscreen();
		setbgcolor(0,0,255-i);
		setcolor(i,0,0);
		movecursor(i % 10,i % 30);
	//movecursor(0,0);
	cout << "Welcome to the Spooky Door" << endl;
	usleep(100'000); //Pauses the program for 10'000 usec
	}
	cout << RESET;
	resetcolor();
	//Ocean Blue: 35, 125, 150

	//Move a monster on the screen
	const auto [ROWS,COLS] = get_terminal_size(); //How big the screen
	cout << ROWS << " " << COLS << endl;
	int x = COLS / 2;
	int y = ROWS / 2;
	setcolor(53,97,43);
	//cin requires raw mode off
	//quick_read requires raw mode on
	//You can switch back and forth as you like
	set_raw_mode(true); //Nonblocking I/O
	while (true) {
	int ch = quick_read(); //Read from the keyboard
	if (ch == ERR) {
	//cout << "User didn't type anything!\n";
	usleep(100'000);
	}
	if (ch == 'Q' or ch == 'q') break;
	if (ch == UP_ARROW) y--;
	if (ch == DOWN_ARROW) y++;
	if (ch == LEFT_ARROW) x--;
	if (ch == RIGHT_ARROW) x++;
	y = clamp(y,0,ROWS-2);
	x = clamp(x,0,COLS-2);
	clearscreen();
	movecursor(y,x);
	cout << "🐰" << endl;
	}
	//Clean up after yourself
	set_raw_mode(false);
	resetcolor();
	set_cursor_mode(true);
	clearscreen();
	*/

	//*TODO non blocking IO demo code


	const int ROWS = world_map.size();
	const int COLS = world_map.at(0).size(); //MAKE SURE ALL ROWS ARE THE SAME SIZE OR BAD TIMES
	const int FPS = 60;
	int row = ROWS / 2, col = COLS / 2;
	int last_row = -1, last_col = -1; //Save our last position so we only redraw on update
	set_raw_mode(true);
	show_cursor(false);
	while (true) {
		int c = toupper(quick_read());
		if (c == 'Q') break;
		if (c == 'W' or c == UP_ARROW) row--;
		if (c == 'S' or c == DOWN_ARROW) row++;
		if (c == 'A' or c == LEFT_ARROW) col--;
		if (c == 'D' or c == RIGHT_ARROW) col++;
		if (!(row == last_row and col == last_col)) { //If we moved...
			print_world(row, col); //...redraw the map
			last_row = row;
			last_col = col;
			movecursor(2, COLS + 5);
			cout << BLUE << "ROW: " << row << RED << " COL: " << col << RESET;
			movecursor(ROWS + 2, 0);
			cout << "Welcome to the game\n";
			cout.flush();
		}
		//make the walls actually work
		if (get_world_location(row, col) == '-') {
			if (c == 'W' or c == UP_ARROW) {
				row += 1;
			} else {
				row -= 1;
			}
		}
		if (get_world_location(row, col) == '|') {
			if (c == 'A' or c == LEFT_ARROW) {
				col += 1;
			} else {
				col -= 1;
			}
		}
		//PUZZLE 1:
		//Collision detection for the "shells"
		if (get_world_location(row, col) == 'S') {
			set_world_location(row, col, ' ');
			movecursor(ROWS + 2, 0);
			cout << "You picked up a shell!\n";
		}
		if (get_world_location(row, col) == 'B') {
			set_world_location(row, col, ' ');
			movecursor(ROWS + 2, 0);
			cout << "You picked up the winning shell!\n";
			for (int i = 1; i < 31; i++) {
				set_world_location(14, i, '~');
			}
		}
		//END PUZZLE 1

		//idk why but when i comment out the code in asterisks it breaks the program lol
		//specifically it says there's mismatched curly braces
		//*
		if (get_world_location(row, col) == 'z') {
			movecursor(ROWS + 2, 0);
			cout << "YOU WIN!!!!!!!!!\n";
			usleep(2'000'000);
			break;
		}//*
		//so we should probably fix that at some point
		if (c == ERR) usleep(1'000'000 / FPS);
	}


	//MAP ENDS HERE


	//PUZZLE IDEAS:
	//Puzzle 1 is also the introduction to the game. It'll be simple
	// and (hopefully) obvious enough for players to complete.

	//Puzzle 1: The Blue Shell🐚
	//Player will need to find the one blue shell out of the several shells in the area alotted
	// and place it in the box next to the sign

	//The puzzles are really tied to the world map so I will get more actual code here once the world map
	// has been fleshed out a bit better

	//Puzzle 2: The Locked Door
	//There will be a locked door blocking the player's path.
	//Player will need to search through several objects like coral/rocks/etc. to find the key
	//Player will need to bring the key back to the door to unlock it and progress

	//Puzzle 3: The crow
	//Player has to find a "pretty thing" for a crow 🐦
	// that pretty thing is a pearl ⚪ in an oyster
	//The crow will not let the player pas until he's been given the pearl
	/*
	   🌟⭐💎
	   ✨ 🐦 💍
	   🪙 📿 ✨

	   CROW
	 *squak* shinies *squak*
	 -----------------------
	 bring me *squak* something pretty
	 */
	//For the dialogue side of thigs:
	//After the second or third time you speak to him the game will start giving you hints:
	//"dont oysters make pearls?"
	//"I wonder where I could find an oyster"

	//If the player is struggling to figure out how to open the oysters
	//They'll get hints like:
	//"How would I open this oyster?"
	//"Is there anything I could use to smash this open?"
	//"maybe a rock would work?"

	//Once we've run out of hints it'll just repeat

	//after we smash the oyster it'll leave the pearl ⚪ for the player to pick up
	//the game is in color so it'll make more visual sense in color form





	/*const int ROWS = world_map.size();
	  const int COLS = world_map.at(0).size(); //MAKE SURE ALL ROWS ARE THE SAME SIZE OR BAD TIMES
	  const int FPS = 60;
	  int row = ROWS / 2, col = COLS / 2;
	  int last_row = -1, last_col = -1; //Save our last position so we only redraw on update
	  set_raw_mode(true);
	  show_cursor(false);
	  while (true) {
	  int c = toupper(quick_read());
	  if (c == 'Q') break;
	  if (c == 'W' or c == UP_ARROW) row--;
	  if (c == 'S' or c == DOWN_ARROW) row++;
	  if (c == 'A' or c == LEFT_ARROW) col--;
	  if (c == 'D' or c == RIGHT_ARROW) col++;
	  if (!(row == last_row and col == last_col)) { //If we moved...
	  print_world(row, col); //...redraw the map
	  last_row = row;
	  last_col = col;
	  movecursor(2, COLS + 5);
	  cout << BLUE << "ROW: " << row << RED << " COL: " << col << RESET;
	  movecursor(ROWS + 2, 0);
	  cout << "Welcome to the game\n";
	  cout.flush();
	  }
	  if (get_world_location(row, col) == "r") {
	  set_world_location(row, col, " ");
	  movecursor(ROWS + 2, 0);
	  cout << "You picked up a radish!\n";
	  }
	  if (get_world_location(row, col) == "z") {
	  movecursor(ROWS + 2, 0);
	  cout << "YOU WIN!!!!!!!!!^G^G^G\n";
	  usleep(2'000'000);
	  break;
	  }
	  if (c == ERR) usleep(1'000'000 / FPS);
	  }
	  set_raw_mode(false);
	  show_cursor(true);
	  movecursor(0, 0);
	  clearscreen(); */

	//VERY END OF CODE, CLEARS SCREEN AND GETS RID OF MAP STUFF


	set_raw_mode(false);
	show_cursor(true);
	movecursor(0, 0);
	clearscreen();


}


