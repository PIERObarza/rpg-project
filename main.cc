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
			if (row == player_row and col == player_col) cout << '@';
			else
				cout << world_map.at(row).at(col);
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
		if (get_world_location(row, col) == 'S') {
			set_world_location(row, col, ' ');
			movecursor(ROWS + 2, 0);
			cout << "You picked up a shell!\n";
		}
		if (get_world_location(row, col) == 'B') {
			set_world_location(row, col, ' ');
			movecursor(ROWS + 2, 0);
			cout << "You picked up the winning shell!\n";
			for (int i = 0; i < last_col; i++) {
				set_world_location(row, i, '~');
			}
		}
		if (get_world_location(row, col) == 'z') {
			movecursor(ROWS + 2, 0);
			cout << "YOU WIN!!!!!!!!!\n";
			usleep(2'000'000);
			break;
		}
		if (c == ERR) usleep(1'000'000 / FPS);
	}


//MAP ENDS HERE


	//Puzzle 1: find the blue shell🐚 and put it in the box
	//Player will need to find the one blue shell out of the several shells in the small area alotted

	/*const auto [ROWS, COLS] = get_terminal_size();
	cout << ROWS*/

//VERY END OF CODE, CLEARS SCREEN AND GETS RID OF MAP STUFF


	set_raw_mode(false);
	show_cursor(true);
	movecursor(0, 0);
	clearscreen();


}


