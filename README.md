# rpg-project
Haven - Puzzles
Tran - Colors & Combat system
Cook - World Map.

For the World Map criteria we have one map that the player is capable of moving around and interacting with.

2) Combat of some sort, and some way of winning the game
NEED TO ADD IN COMBAT SYSTEM

For the colors criteria, the game includes many colors in the world map, dialogue system, and inventory system.
For the puzzles criteria, the game has 5 puzzles using many different mechanics.
For the dialogue criteria, the game includes 41 lines of dialogue, descriptions of the world, and info about what the player picked up.

For extra credit, the game uses Nonblocking I/O as the world map/movement system. 
For extra credit, the game has an inventory system. The Inventory struct tracks the name, icon, and color of items that the player picks up and prints them to the screen.


We are using variables by storing the world map in a vector, storing the users keystrokes in a char, storing the player's location in integers, etc.

Algebra is being used when row and col is added or subracted to and when the dialogue counters are incremented

Input and Output is the basis of the game. When a user inputs a keystroke (W,A,S,D, arrow keys) the program runs and outputs the player's updated position, along with informing them what
happened in the game.

Branches are used to detect if a player is interacting with an item/enemy/wall in the game. When the player moves, the code checks if the space they moved to is a certain character or not. If it is, the game outputs accordingly.

Loops are used to run the game. The while() loops reads key strokes, runs the contents of the loop and repeats until a break point.

Functions are used to get the character at a location, set the character at a location, and print the world map to the screen.

We used a struct to make the inventory system. The member variables are the name, icon, and color. These describe the characteristics of the items that the player picks up in the game. There's currently one member function, which prints the items in the player's inventory to the screen.
