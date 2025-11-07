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

/*
//Global Variable - accessible in all functions below
vector<string> world_map = {
	"************",
	"* r   |    *",
	"*  s  | d  *",
	"*     |    *",
	"*   x ---  *",
	"*        z *",
	"*      g   *",
	"* d        *",
	"*    s r   *",
	"************"
};

string get_world_location(size_t row, size_t col) {
	if (row >= world_map.size()) return " ";
	if (col >= world_map.at(row).size()) return " ";
	string temp;
	temp.push_back(world_map.at(row).at(col));
	return temp;
}

void set_world_location(size_t row, size_t col, string c) {
	if (row >= world_map.size()) return;
	if (col >= world_map.at(row).size()) return;
	string temp;
	temp.push_back(world_map.at(row).at(col));
	temp = c;
}

void print_world(size_t player_row, size_t player_col) {
	clearscreen();
	movecursor(0, 0);
	for (size_t row = 0; row < world_map.size(); row++) {
		for (size_t col = 0; col < world_map.at(row).size(); col++) {
			if (row == player_row and col == player_col) cout << "🦦";
			else
				cout << world_map.at(row).at(col);
		}
		cout << endl;
	}
}
*/
int main() {
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






	//All the stuff below was me playing around with the sample programs we were given
	/*const auto [ROWS, COLS] = get_terminal_size(); //How big the screen
	cout << ROWS << " " << COLS << endl;
	int x = COLS / 2;
	int y = ROWS / 2;
	setcolor(171, 113, 57); //sets player color
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
		y = clamp(y, 0, ROWS - 2);
		x = clamp(x, 0, COLS - 2);
		clearscreen();
		movecursor(y, x);
		cout << "🦦" << endl;
		cout << "🐚" << endl;
	}
	//Clean up after yourself
	set_raw_mode(false);
	resetcolor();
	set_cursor_mode(true);
	clearscreen();*/

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

}

