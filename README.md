# rpg-project

We are using variables by storing the world map in a vector, storing the users keystrokes in a char, storing the player's location in integers, etc.

Algebra is being used when row and col is added or subracted to

Input and Output is the basis of the game. When a user inputs a keystroke (W,A,S,D, arrow keys) the program runs and outputs the player's updated position, along with informing them what
happened in the game.

Branches are used to detect if a player is interacting with an item/enemy/wall in the game. When the player moves, the code checks if the space they moved to is a certain character or not. If it is, the game outputs accordingly.

Loops are used to run the game. The while() loops reads key strokes, runs the contents of the loop and repeats until a break point.

Functions are used to get the character at a location, set the character at a location, and print the world map to the screen.

We used a struct to make the inventory system. The member variables are the name, icon, and color. These describe the characteristics of the items that the player picks up in the game. There's currently one member function, which prints the items in the player's inventory to the screen.

In the combat system, we used AI to complete the project.

In this part, when the location @ == "G", @ will fight with goblin. Print out the blood, the damage of @ (default blood is 15) and the blood of globin (default blood is 10), and the default damage of both is 2 dame. Next, print out 2 options (A) to attack, (B) to use items. If (A) is chosen, @ will attack and goblin will lose 2 blood points, then goblin will attack @ and @ will lose 2 blood points. Items, can use "Shell🐚" to increase @'s current blood. After winning, @ will be increased by 5 damage, if it fails, the game will end.
