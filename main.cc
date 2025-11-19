//Fill out this comment with your names and which bullet points you did
//Partners: Willems, Tran, Cook, Ugaz
//Bullet Points: Willems - Puzzles & Inventory, Tran - Colors & Combat System, Cook - World Map
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
	"* f               f       |    *",
	"*  S                      | f  *",
	"*          S              |    *",
	"*                       f ---  *",
	"*     ---                    f *",
	"*     |B|                      *",
	"* S   | -- S                   *",
	"*   S |                    f   *",
	"*     ---                      *",
	"*                              *",
	"*------------------------------*", // This row should turn into ~~~~~~~~~~~~~~~~~~~~~~~ once the player picks up the blue shell (B for now), allowing them to now cross it
	"*                        d     *",
	"*       S       |              *",
	"*   ---     --- |   d          *",
	"*               |              *",
	"*   |     |     |   ---        *",
	"*   |  S  |     |              *",
	"*   ---     --- |      S       *",
	"*   |K|--      |   B           *",
	"*   |                          *",
	"*------------------------------*",
	"*   S       |       R          *",
	"*       --- |                  *",
	"*   O       |S         S       *",
	"*   |       |      ---         *",
	"*       S   |    C             *",
	"*   ---     |S                 *",
	"*   S       |          S       *",
	"*           |---               *",
	"*   S                  S  R    *",
	"*------------------------------*", // row 31, unlocks when Pearl given to Crow
	"*       W       |S             *",
	"*   ---     --- |      S       *",
	"*   a       b   |              *",
	"*   |S          |S     ---     *",
	"*       c                      *",
	"*   ---     --- |  S           *",
	"*   S           |              *",
	"*       S       |---           *",
	"*   ---         |        S     *",
	"*------------------------------*", // row 41, unlocks when Walrus questions complete
	"*   f   S   f          S       *",
	"*       ---     |   f          *",
	"*   S       f             S    *",
	"*       |   S   |---           *",
	"*   f       |   |       f      *",
	"*   ---       S |              *",
	"*   S       |       S          *",
	"*   f       |---|       f      *",
	"*   S   f       |S          S  *",
	"*------------------------------*", // row 51, unlocks after all 7 fish eaten
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
			if (row == player_row and col == player_col) cout << '@';
			else if (c == '*') cout << GREEN << c << RESET;
			else if (c == 'B') cout << BLUE << c << RESET;
			else if (c == 'S') cout << RED << c << RESET;
			else if (c == 'r') cout << MAGENTA  << c << RESET;
			else if (c == 'z') cout << BOLDCYAN  << c << RESET;
			else if (c == 'd') cout << YELLOW  << c << RESET;
			else if (c == 'x') cout << BOLDRED  << c << RESET;
			else
				cout << c;
		}
		cout << endl;
	}
}

struct Inventory {
	string name = "none";
	string color = BOLDBLACK;
	string icon = "❌";
	void PrintInventory() {
		if (name != "none") {
			//TODO: add some sort of way to make the inventory less cluttered
			cout << "INVENTORY: ";
			cout << color << name << icon << RESET;
			cout << endl;
		}
	}
};

int main() {
	//vector for the class
	vector<Inventory> InventoryItems;
	//dialogue system counters
	int crowCount = 0;
	int oysterCount = 0;
	bool intro = true;
	int walrusCount = 0;
	int correctCount = 0;
	int wrongCount = 0;
	int fishCount = 0;


	//MAP STARTS HERE
	//TODO non blocking IO demo code

	const int ROWS = world_map.size();
	const int COLS = world_map.at(0).size(); //MAKE SURE ALL ROWS ARE THE SAME SIZE OR BAD TIMES
	const int FPS = 60;
	int row = 2, col = 5;
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
			if (intro) {
				cout << "Welcome to the game\n";
				cout << "In this game, you play as a sea otter exploring the world.\n";
				cout << "For this first level, you need to find the " << BLUE << "Blue Shell🐚" << RESET << endl;
				intro = false;
			}
			for (int i = 0; i < InventoryItems.size(); i++) {
				InventoryItems.at(i).PrintInventory();
			}
			cout.flush();
		}
		//make the walls actually work
		//TODO: make the collitions better
		if (get_world_location(row, col) == '-') {
			if (c == 'A' or c == LEFT_ARROW) {
				col += 1;
			} else if (c == 'D' or c == RIGHT_ARROW) {
				col -= 1;
			} else if (c == 'W' or c == UP_ARROW) {
				row += 1;
			} else {
				row -= 1;
			}
		}
		if (get_world_location(row, col) == '|') {
			if (c == 'A' or c == LEFT_ARROW) {
				col += 1;
			} else if (c == 'D' or c == RIGHT_ARROW) {
				col -= 1;
			} else if (c == 'W' or c == UP_ARROW) {
				row += 1;
			} else {
				row -= 1;
			}
		}
		if (get_world_location(row, col) == '*') {
            if (c == 'A' or c == LEFT_ARROW) {
                col += 1;
            } else if (c == 'D' or c == RIGHT_ARROW) {
                col -= 1;
            } else if (c == 'W' or c == UP_ARROW) {
                row += 1;
            } else {
                row -= 1;
            }
        }
		//PUZZLE 1:
		//Collision detection for the "shells"
		if (get_world_location(row, col) == 'S') {
			set_world_location(row, col, ' ');
			movecursor(ROWS + 2, 0);
			cout << "You picked up a shell!\n";
			Inventory shell;
			shell.name = "Shell";
			shell.icon = "🐚";
			shell.color = BOLDWHITE;
			InventoryItems.push_back(shell);
		}
		if (get_world_location(row, col) == 'B') {
			set_world_location(row, col, ' ');
			movecursor(ROWS + 2, 0);
			cout << "You picked up the blue shell!\n";
			for (int i = 1; i < COLS-1; i++) {
				set_world_location(11, i, '~');
			}
			Inventory blueShell;
			blueShell.name = "Shell";
			blueShell.icon = "🐚";
			blueShell.color = BLUE;
			InventoryItems.push_back(blueShell);
		}
		//END PUZZLE 1
		//PUZZLE 2:
		if (get_world_location(row, col) == 'L') {
			//todo: maybe make this better
			bool key = false;
			for (int i = 0; i < InventoryItems.size(); i++) {
				if (InventoryItems.at(i).name == "Key") {
					key = true;
				}
			}
			if (key) {
				set_world_location(row, col, ' ');
				movecursor(ROWS + 2, 0);
				cout << "You unlocked🔓 the lock!\n";
			} else {
				if (c == 'A' or c == LEFT_ARROW) {
					col += 1;
				} else if (c == 'S' or c == RIGHT_ARROW) {
					col -= 1;
				} else if (c == 'W' or c == UP_ARROW) {
					row += 1;
				} else {
					row -= 1;
				}
				cout << "It's locked🔒\n";
			}
		}
		if (get_world_location(row, col) == 'K') {
			set_world_location(row, col, ' ');
			movecursor(ROWS + 2, 0);
			cout << "You picked up the key!\n";
			for (int i = 1; i < COLS-1; i++) {
				set_world_location(21, i, '~');
			}
			Inventory key;
			key.name = "Key";
			key.icon = "🔑";
			key.color = YELLOW;
			InventoryItems.push_back(key);
		}
		//END PUZZLE 2
		//PUZZLE 3:
		//TODO: make this less bad
		if (get_world_location(row, col) == 'C') {
			bool pearl = false;
			int index = 0;
			for (int i = 0; i < InventoryItems.size(); i++) {
				if (InventoryItems.at(i).name == "Pearl") {
					pearl = true;
					index = i;
				}
			}
			if (pearl) {
				cout << BOLDBLACK << "CROW🐦:" << RESET << endl;
				cout << "*squak* thank you!\n";
				set_world_location(row, col, ' ');
				movecursor(ROWS + 2, 0);
					for (int i = 1; i < COLS-1; i++) {
					    set_world_location(31, i, '~');
					}
				//TODO: remove pearl from inventory
				InventoryItems.erase(InventoryItems.begin() + index);
			} else {
				if (crowCount > 3) crowCount = 0;
				if (crowCount < 2) {
					if (c == 'A' or c == LEFT_ARROW) {
						col += 1;
					} else if (c == 'D' or c == RIGHT_ARROW) {
						col -= 1;
					} else if (c == 'W' or c == UP_ARROW) {
						row += 1;
					} else {
						row -= 1;
					}
					cout << BOLDBLACK << "CROW🐦:" << RESET << endl;
					cout << "*squak* shinies *squak*" << endl;
					cout << "bring me *squak* something pretty" << endl;
					crowCount ++;
					usleep(2'000'000);
				} else if (crowCount == 2) {
					if (c == 'A' or c == LEFT_ARROW) {
						col += 1;
					} else if (c == 'D' or c == RIGHT_ARROW) {
						col -= 1;
					} else if (c == 'W' or c == UP_ARROW) {
						row += 1;
					} else {
						row -= 1;
					}
					cout << "dont oysters make pearls?" << endl;
					crowCount ++;
					usleep(2'000'000);
				} else if (crowCount == 3) {
					if (c == 'A' or c == LEFT_ARROW) {
						col += 1;
					} else if (c == 'D' or c == RIGHT_ARROW) {
						col -= 1;
					} else if (c == 'W' or c == UP_ARROW) {
						row += 1;
					} else {
						row -= 1;
					}
					cout << "I wonder where I could find an oyster" << endl;
					crowCount ++;
					usleep(2'000'000);
				}
			}
		}
		if (get_world_location(row, col) == 'R') {
			set_world_location(row, col, ' ');
			movecursor(ROWS + 2, 0);
			cout << "You picked a rock🪨!\n";
			Inventory rock;
			rock.name = "Rock";
			rock.icon = "🪨";
			rock.color = BOLDBLACK;
			InventoryItems.push_back(rock);
		}
		if (get_world_location(row, col) == 'O') {
			bool rock = false;
			for (int i = 0; i < InventoryItems.size(); i++) {
				if (InventoryItems.at(i).name == "Rock") {
					rock = true;
				}
			}
			if (rock) {
				set_world_location(row, col, ' ');
				movecursor(ROWS + 2, 0);
				cout << "You broke open the oyster🦪!\n";
				cout << "You obtained a Pearl⚪!\n";
				Inventory pearl;
				pearl.name = "Pearl";
				pearl.icon = "⚪";
				pearl.color = BOLDWHITE;
				InventoryItems.push_back(pearl);
			} else {
				//I used AI to debug the code from here
				if (oysterCount > 4) oysterCount = 0;
				if (oysterCount < 2) {
					if (c == 'A' or c == LEFT_ARROW) {
						col += 1;
					} else if (c == 'D' or c == RIGHT_ARROW) {
						col -= 1;
					} else if (c == 'W' or c == UP_ARROW) {
						row += 1;
					} else {
						row -= 1;
					}
					cout << "It's an oyster🦪\n";
					oysterCount ++;
					usleep(2'000'000);
				} else if (oysterCount == 2) {
					if (c == 'A' or c == LEFT_ARROW) {
						col += 1;
					} else if (c == 'D' or c == RIGHT_ARROW) {
						col -= 1;
					} else if (c == 'W' or c == UP_ARROW) {
						row += 1;
					} else {
						row -= 1;
					}
					cout << "How would I open this oyster?" << endl;
					oysterCount ++;
					usleep(2'000'000);
				} else if (oysterCount == 3) {
					if (c == 'A' or c == LEFT_ARROW) {
						col += 1;
					} else if (c == 'D' or c == RIGHT_ARROW) {
						col -= 1;
					} else if (c == 'W' or c == UP_ARROW) {
						row += 1;
					} else {
						row -= 1;
					}
					cout << "Is there anything I could use to smash this open?" << endl;
					oysterCount ++;
					usleep(2'000'000);
				}  else if (oysterCount == 4) {
					if (c == 'A' or c == LEFT_ARROW) {
						col += 1;
					} else if (c == 'D' or c == RIGHT_ARROW) {
						col -= 1;
					} else if (c == 'W' or c == UP_ARROW) {
						row += 1;
					} else {
						row -= 1;
					}
					// Puzzle 3 door
					cout << "maybe a rock would work?" << endl;
					oysterCount ++;
					usleep(2'000'000);
				}
			}
			//To here
		}
		//END PUZZLE 3
		//PUZZLE 4:
		//WALRUS RIDDLES
		//its literally just a walrus asking riddles
		if (get_world_location(row, col) == 'W') {
			if (walrusCount == 0) {
				if (c == 'A' or c == LEFT_ARROW) {
					col += 1;
				} else if (c == 'D' or c == RIGHT_ARROW) {
					col -= 1;
				} else if (c == 'W' or c == UP_ARROW) {
					row += 1;
				} else {
					row -= 1;
				}
				cout << CYAN << "WALRUS🦭:" << RESET << endl;
				cout << "Hello, answer my trivia if you wish to pass" << endl;
				cout << "First question: With which fish species do anemones have a symbiotic relationship?" << endl;
				cout << "Is it a) The Catfish, b) The Shrimp, or c) The Clownfish?\n";
				set_world_location(13, 23, 'a');
				set_world_location(13, 25, 'b');
				set_world_location(13, 27, 'c');
				usleep(3'000'000);
			} else if (walrusCount == 1) {
				if (c == 'A' or c == LEFT_ARROW) {
					col += 1;
				} else if (c == 'D' or c == RIGHT_ARROW) {
					col -= 1;
				} else if (c == 'W' or c == UP_ARROW) {
					row += 1;
				} else {
					row -= 1;
				}
				cout << CYAN << "WALRUS🦭:" << RESET << endl;
				cout << "Question 2: What is the largest species of shark?" << endl;
				cout << "Is it a) The Great White Shark, b) The Whale Shark, or c) The Hammerhead Shark?\n";
				set_world_location(13, 23, 'a');
				set_world_location(13, 25, 'b');
				set_world_location(13, 27, 'c');
				usleep(3'000'000);
			} else if (walrusCount == 2) {
				if (c == 'A' or c == LEFT_ARROW) {
					col += 1;
				} else if (c == 'D' or c == RIGHT_ARROW) {
					col -= 1;
				} else if (c == 'W' or c == UP_ARROW) {
					row += 1;
				} else {
					row -= 1;
				}
				cout << CYAN << "WALRUS🦭:" << RESET << endl;
				cout << "Final Question: What is the term for light produced by marine animals?" << endl;
				cout << "Is it a) Bioluminescence, b) Waterlights, or c) Sealumens?\n";
				set_world_location(13, 23, 'a');
				set_world_location(13, 25, 'b');
				set_world_location(13, 27, 'c');
				usleep(3'000'000);
			}
			//I used AI to debug starting here
			else if (walrusCount == 3) {
				for (int i = 0; i < InventoryItems.size(); i++) {
					if ((InventoryItems.at(i).name == "c) The Clownfish") || (InventoryItems.at(i).name == "b) The Whale Shark") || (InventoryItems.at(i).name == "a) Bioluminescence")) {
						correctCount++;
					} else if (InventoryItems.at(i).name == "Wrong!") {
						wrongCount++;
					}
				}
				if (correctCount == 3) {
					if (c == 'A' or c == LEFT_ARROW) {
						col += 1;
					} else if (c == 'D' or c == RIGHT_ARROW) {
						col -= 1;
					} else if (c == 'W' or c == UP_ARROW) {
						row += 1;
					} else {
						row -= 1;
					}
					cout << CYAN << "WALRUS🦭:" << RESET << endl;
					cout << "Well done! You got all 3 questions right, you may pass\n";
					for (int i = 1; i < COLS-1; i++) {
					    set_world_location(41, i, '~');
					}
					usleep(2'000'000);
				} else if (correctCount == 2) {
					if (c == 'A' or c == LEFT_ARROW) {
						col += 1;
					} else if (c == 'D' or c == RIGHT_ARROW) {
						col -= 1;
					} else if (c == 'W' or c == UP_ARROW) {
						row += 1;
					} else {
						row -= 1;
					}
					cout << CYAN << "WALRUS🦭:" << RESET << endl;
					cout << "Thats a passing score, I'll let you go.\n";
					for (int i = 1; i < COLS-1; i++) {
					    set_world_location(41, i, '~');
					}
					usleep(2'000'000);
				} else if (correctCount == 1) {
					if (c == 'A' or c == LEFT_ARROW) {
						col += 1;
					} else if (c == 'D' or c == RIGHT_ARROW) {
						col -= 1;
					} else if (c == 'W' or c == UP_ARROW) {
						row += 1;
					} else {
						row -= 1;
					}
					cout << CYAN << "WALRUS🦭:" << RESET << endl;
					cout << "I feel bad, you can pass.\n";
					for (int i = 1; i < COLS-1; i++) {
					    set_world_location(41, i, '~');
					}
					usleep(2'000'000);
				} else if (wrongCount == 3) {
					if (c == 'A' or c == LEFT_ARROW) {
						col += 1;
					} else if (c == 'D' or c == RIGHT_ARROW) {
						col -= 1;
					} else if (c == 'W' or c == UP_ARROW) {
						row += 1;
					} else {
						row -= 1;
					}
					cout << CYAN << "WALRUS🦭:" << RESET << endl;
					cout << "Did you even try? Whatever, just get out of here already.\n";
					for (int i = 1; i < COLS-1; i++) {
					    set_world_location(41, i, '~');
					}
					usleep(2'000'000);
				}
			}
			//And ending here
		}

		if (walrusCount == 0) {
			if (get_world_location(row, col) == 'c') {
				cout << CYAN << "WALRUS🦭:" << RESET << endl;
				cout << "Correct! It is the clownfish.\n";
				cout << "Come to me to recieve your next question." << endl;
				//deletes a, b, and c from the world, the numbers can be changed as need be
				set_world_location(13, 23, ' ');
				set_world_location(13, 25, ' ');
				set_world_location(13, 27, ' ');
				movecursor(ROWS + 2, 0);
				Inventory right1;
				right1.name = "c) The Clownfish";
				right1.icon = "🐠";
				right1.color = YELLOW;
				//OPTIONAL: figure out how to make the text orange
				InventoryItems.push_back(right1);
				walrusCount ++;
			} else if ((get_world_location(row, col) == 'b') || (get_world_location(row, col) == 'a')) {
				cout << CYAN << "WALRUS🦭:" << RESET << endl;
				cout << "That is incorrect. The answer was the clownfish. Have you ever seen Finding Nemo?" << endl;
				cout << "Come to me to recieve your next question." << endl;
				set_world_location(13, 23, ' ');
				set_world_location(13, 25, ' ');
				set_world_location(13, 27, ' ');
				movecursor(ROWS + 2, 0);
				Inventory wrong1;
				wrong1.name = "Wrong!";
				wrong1.icon = "❌";
				wrong1.color = RED;
				InventoryItems.push_back(wrong1);
				walrusCount ++;
			}
		} else if (walrusCount == 1) {
			if (get_world_location(row, col) == 'b') {
				cout << CYAN << "WALRUS🦭:" << RESET << endl;
				cout << "Correct! It is the whale shark.\n";
				cout << "Come to me to recieve your final question." << endl;
				set_world_location(13, 23, ' ');
				set_world_location(13, 25, ' ');
				set_world_location(13, 27, ' ');
				movecursor(ROWS + 2, 0);
				Inventory right2;
				right2.name = "b) The Whale Shark";
				right2.icon = "🦈";
				right2.color = BOLDBLACK;
				InventoryItems.push_back(right2);
				walrusCount ++;
			} else if ((get_world_location(row, col) == 'c') || (get_world_location(row, col) == 'a')) {
				cout << CYAN << "WALRUS🦭:" << RESET << endl;
				cout << "That is incorrect. The largest shark is actually the whale shark.\n";
				cout << "Come to me to recieve your final question." << endl;
				set_world_location(13, 23, ' ');
				set_world_location(13, 25, ' ');
				set_world_location(13, 27, ' ');
				movecursor(ROWS + 2, 0);
				Inventory wrong2;
				wrong2.name = "Wrong!";
				wrong2.icon = "❌";
				wrong2.color = RED;
				InventoryItems.push_back(wrong2);
				walrusCount ++;
			}
		} else if (walrusCount == 2) {
			if (get_world_location(row, col) == 'a') {
				cout << CYAN << "WALRUS🦭:" << RESET << endl;
				cout << "Correct! It is bioluminescence.\n";
				cout << "Come to me to recieve your score." << endl;
				set_world_location(13, 23, ' ');
				set_world_location(13, 25, ' ');
				set_world_location(13, 27, ' ');
				movecursor(ROWS + 2, 0);
				Inventory right3;
				right3.name = "a) Bioluminescence";
				right3.icon = "💡";
				right3.color = BLUE;
				InventoryItems.push_back(right3);
				walrusCount ++;
			} else if ((get_world_location(row, col) == 'c') || (get_world_location(row, col) == 'b')) {
				cout << CYAN << "WALRUS🦭:" << RESET << endl;
				cout << "That is incorrect. The correct term is bioluminescence. Waterlights are something in Terraria and I just made up sealumens.\n";
				cout << "Come to me to recieve your score." << endl;
				set_world_location(13, 23, ' ');
				set_world_location(13, 25, ' ');
				set_world_location(13, 27, ' ');
				movecursor(ROWS + 2, 0);
				Inventory wrong3;
				wrong3.name = "Wrong!";
				wrong3.icon = "❌";
				wrong3.color = RED;
				InventoryItems.push_back(wrong3);
				walrusCount ++;
			}
		}
		//END OF PUZZLE 4
		//PUZZLE 5
		//Eat all the fish
		//for the sake of getting the game done, the player needs to eat all 7 fish to win.
		//but that number can be changed idc
		if (get_world_location(row, col) == 'f') {
			set_world_location(row, col, ' ');
			movecursor(ROWS + 2, 0);
			cout << "You ate a fish!\n";
			for (int i = 1; i < COLS-1; i++) {
				set_world_location(51, i, '~');
			}
			Inventory fish;
			fish.name = "Fish";
			fish.icon = "🐟";
			fish.color = BOLDBLUE;
			InventoryItems.push_back(fish);
			fishCount++;
		}

		//idk why but when i comment out the code in asterisks it breaks the program lol
		//specifically it says there's mismatched curly braces
		//*
		if (fishCount == 7) {
			movecursor(ROWS + 2, 0);
			for (int i = 1; i < COLS-1; i++) {
			    set_world_location(41, i, '~');
			}
			cout << "YOU WIN!!!!!!!!!\n";
			usleep(2'000'000);
			break;
		}//*
		//so we should probably fix that at some point
		if (c == ERR) usleep(1'000'000 / FPS);
	}
	//END PUZZLE 5


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


	//VERY END OF CODE, CLEARS SCREEN AND GETS RID OF MAP STUFF


	set_raw_mode(false);
	show_cursor(true);
	movecursor(0, 0);
	clearscreen();


}


