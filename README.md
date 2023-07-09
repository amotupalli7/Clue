# Clue## How to compile the game and run Clue

1. Open up the terminal, make sure you are in the folder path of the project( ls will print all the files ), and use this command:

2. gcc -o clue adventure.c

3. run ./clue in the terminal to play the game




## Overall/Description of Game Structure corresponding to rubric

2a) The game board is set up in a grid of 9 Room structs. There exists a grid array in which there are 9 pointers to these rooms. Each Room Struct is fixed in place in orderto most easily set up the pointers from one to the next. However, the randomization of the rooms still exist since the rooms have no features yet and will be randomly assigned names, characters, and items later.

2b) The shuffle method is called on both the roomNames and characters before the grid is intialized, the items are always going to be in the grid location, however since the roomNames are randomized, that means the each item is assigned to a different room everytime. 

2b) This shuffle is done with the shuffle and swap methods defined in adventure.c 

2c) At the beginning of the code 9 room names, 5 characters, and 6 items have been declared in arrays. There are some extra NULL "strings" in itemList just to make them the same size as the room list array.

2c) Each room is only assigned one item at max in the for loop that comes after the grid declaration.

2d) The room, item, and character that are the answer are right before the grid pointers are declared around line 85

2e) The room struct as declared in rooms.h has a linked list of items called itemList

2f) The avatar struct as defined in adventure.c near line 69 also has the same linkedlist implementation for its inventory

2g) All the commands are in adventure.c under the function handleUserInput

2h) Game state: this is kept track with a gameOver variable defined in adventure.c, this variable will turn true if the player correctly guesses all the correct information or is unable to guess correctly in 10 attempts

2h) The prompts with clue are in the clueCommand function and all invalid entries or mistypes are handled there

2h) The moving of a character into a room is done by the swapCharacter function in rooms.c, everytime a character is guessed, they will come into the room that the avatar is in and will swap with the character currently in the room

Overall User Input: There is one main loop that will keep reading for commands but the specifics with each command is handled in each corresponding function which are called in handleUuserInput




