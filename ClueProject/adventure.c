#include "rooms.c"
#include "items.c"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define MAXCHARLENGTH 100

_Bool gameOver = false; // Boolean that keeps track whether game should be over or not


char* roomNames[9] = {"kitchen",
			       "ballroom",
			       "conservatory",
			       "dining room",
			       "billiard room",
			       "library",
			       "lounge",
			       "hall",
			       "study"
                    };

char* itemList[12] = {
		      "candlestick",
		      "dagger",
		      "lead pipe",
		      "revolver",
		      "rope",
		      "wrench",
              "NULL",
              "NULL",
              "NULL"
};

char* characters[20] = {"Miss Scarlet", 
                        "Colonel Mustard", 
                        "Mrs. White", 
                        "The Reverend Green", 
                        "Mrs. Peacock"};



void swap(char* arr[], int i, int j)
{
    char* temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void shuffle(char* arr[], int n)
{
    
    for (int i = n - 1; i >= 1; i--)
    {
        srand(time(NULL));
        int j = rand() % (i + 1);
        swap(arr, i, j);
    }
}

int returnRandInt(int n){
    srand(time(NULL));
    int x = rand() % n;
    return x;
}

typedef struct Avatar{
    ItemNode* inventory;
    Room* currRoom;
}Avatar;



int main(){
////////////////////// Setting up the game grid //////////////////////////////////////////////////////////
    Room *grid; // representation of the 3x3 Room grid
    grid = (Room*) calloc(9, sizeof(Room)); // Initializes an array of 9 rooms
    
    shuffle(roomNames,9);
    shuffle(characters,5);
    
    // These 3 "strings" are the answer to the game
    char* murderWeapon = itemList[returnRandInt(6)]; 
    char* murderer = characters[returnRandInt(5)];
    char* murderRoom = roomNames[returnRandInt(9)];

    int attempts = 0; // keeps track of the number of attempts player has made

    // Setting up the grid with pointers, even though the grid may be fixed, the rooms are randomly assigned since no characteristics of the room have been assigned yet
    grid[0].name = roomNames[0]; grid[0].North = NULL;     grid[0].South = &grid[3]; grid[0].West = NULL;     grid[0].East = &grid[1]; //grid0 = { .North = NULL, .South = &grid[3], .West = NULL, .East = &grid1};
    grid[1].name = roomNames[1]; grid[1].North = NULL;     grid[1].South = &grid[4]; grid[1].West = &grid[0]; grid[1].East = &grid[2]; //grid1 = { .North = NULL, .South = &grid4, .West = &grid0, .East = &grid2};
    grid[2].name = roomNames[2]; grid[2].North = NULL;     grid[2].South = &grid[5]; grid[2].West = &grid[4]; grid[2].East = NULL; //grid2 = { .North = NULL, .South = &grid5, .West = &grid4, .East = NULL};
    grid[3].name = roomNames[3]; grid[3].North=&grid[0];   grid[3].South = &grid[6]; grid[3].West = NULL;     grid[3].East = &grid[4]; //grid3 = { .North = &grid0, .South = &grid6, .West = NULL, .East = &grid4};
    grid[4].name = roomNames[4]; grid[4].North = &grid[1]; grid[4].South = &grid[7]; grid[4].West = &grid[3]; grid[4].East = &grid[5]; //grid4 = { .North = &grid1, .South = &grid7, .West = &grid3, .East = &grid5};
    grid[5].name = roomNames[5]; grid[5].North = &grid[2]; grid[5].South = &grid[8]; grid[5].West = &grid[4]; grid[5].East = NULL; //grid5 = { .North = &grid2, .South = &grid8, .West = &grid4, .East = NULL};
    grid[6].name = roomNames[6]; grid[6].North = &grid[3]; grid[6].South = NULL;     grid[6].West = NULL;     grid[6].East = &grid[7]; //grid6 = { .North = &grid3, .South = NULL, .West = NULL, .East = &grid7};
    grid[7].name = roomNames[7]; grid[7].North = &grid[4]; grid[7].South = NULL;     grid[7].West = &grid[6]; grid[7].East = &grid[8]; //grid7 = { .North = &grid4, .South = NULL, .West = &grid6, .East = &grid8};
    grid[8].name = roomNames[8]; grid[8].North = &grid[5]; grid[8].South = NULL;     grid[8].West = &grid[7]; grid[8].East = NULL; //grid8 = { .North = &grid5, .South = NULL, .West = &grid7, .East = NULL};


    
    for(int x=0;x<9;x++){  // give 6 rooms items and 5 characters
        
        if(itemList[x]!="NULL"){
            // make the list node 
            ItemNode* node = initializeNode(itemList[x]);
            grid[x].itemList = node;
        }
        if(x<5){ // assign character to room
            grid[x].character = characters[x];
        }
    }

/////////////////////////  Making the Avatar ////////////////////////////
Avatar player;
player.inventory = NULL;
player.currRoom = &(grid[returnRandInt(9)]);


////////////////// Game functions ////////////////////////////////////////////


void helpTable(){
    printf("Command \t Description \n");
    printf("_________________________________\n");
    printf("help: \t Lookup commands in the table \n");
    printf("list: \t Lookup list of characters, rooms and items. \n");
    printf("look: \t See what room you are in, rooms around you, items in the room and characters in the room.\n");
    printf("go: \t Move your avatar in a certain direction. After submitting this command, type North, South, East, or West when the prompt shows up and if it is valid you will travel in that direction\n");
    printf("take: \t Pick up a certain item which should be in the current room of the avatar. Like go, type the item after submitting this command. \n");
    printf("drop: \t Allows player to drop an item from their inventory to the room they are currently in.\n");
    printf("inventory: \t Lists out the avatars inventory.\n");
    printf("clue: \t Make a guess about who did the murder and the item that they used to do it. Follow the prompts after calling this commmand.\n");

}
void listCommand(){
        //loop through all the names of rooms, items, and characters and print if they are not "NULL"
        printf("Rooms: ");
        for(int x = 0;x<9;x++){
            printf("%s,", roomNames[x]);
        }
        printf("\nItems: ");
        for(int x = 0;x<9;x++){
            if(itemList[x]!="NULL"){
                printf("%s,", itemList[x]);
            }
        }
        printf("\nCharacters: ");
        for(int x = 0;x<5;x++){
            printf("%s,", characters[x]);
        }
        printf("\n");
}
void lookCommand(){
    printf("You are in the %s.\n", player.currRoom->name);
    
    ItemNode* roomsItems = player.currRoom->itemList;
    printf("Items in this room: ");
    roomsItems == NULL ? printf("no items\n") : printElements(player.currRoom->itemList);

    char* roomsChar = player.currRoom->character;
    printf("Character in this room: ");
    roomsChar == NULL ? printf("nobody\n") : printf("%s\n", roomsChar);

    Room* room = player.currRoom;
    if(room->North != NULL){printf("north: %s\n", room->North->name);}
    if(room->South != NULL){printf("south: %s\n", room->South->name);}
    if(room->East != NULL){printf("east: %s\n", room->East->name);}
    if(room->West != NULL){printf("west: %s\n", room->West->name);}


}

_Bool isValidMove(char* direction){
    // if the direction is not equal to null in the avatars currRoom then its valid
    if(strcmp(direction,"north")==0) {
        return player.currRoom->North !=NULL;
    }
    if(strcmp(direction,"south")==0){
        return player.currRoom->South !=NULL;
    }
    if(strcmp(direction,"east")==0){
        return player.currRoom->East !=NULL;
    }
    if(strcmp(direction,"west")==0){
        return player.currRoom->West !=NULL;
    }
    else{
        return false;
    }
}

void goCommand(){
    //give a prompt to get direction 
    char* userInput = malloc(sizeof(char) * MAXCHARLENGTH);
    size_t inputSize = MAXCHARLENGTH;
    
    while(!isValidMove(userInput)){

            printf("Enter a valid direction: ");
            Room* room = player.currRoom;
            if(room->North != NULL){printf("north ");}
            if(room->South != NULL){printf("south ");}
            if(room->East != NULL){printf("east ");}
            if(room->West != NULL){printf("west");}

            printf("\n");
            
            getline(&userInput, &inputSize, stdin);
            int cLen = strlen(userInput);
            userInput[cLen-1] = '\0';
    }
    
    if(strcmp(userInput,"north")==0) {
        player.currRoom = player.currRoom->North;
    }
    if(strcmp(userInput,"south")==0){
        player.currRoom = player.currRoom->South;
    }
    if(strcmp(userInput,"east")==0){
        player.currRoom = player.currRoom->East;
    }
    if(strcmp(userInput,"west")==0){
        player.currRoom = player.currRoom->West;
    }

    printf("You have moved %s.\n", userInput);

    lookCommand();

}

_Bool itemCanBeTaken(ItemNode* headNode, char* item){
    // if the item is in the currRoom's linked list then it can be taken

    ItemNode* temp = headNode;

    while(temp!=NULL){
        if(strcmp(temp->itemName,item)==0){
            return true;
        }
        temp = temp->next;
    }
    return false;
    

}
void takeCommand(){

    char* userInput = malloc(sizeof(char) * MAXCHARLENGTH);
    size_t inputSize = MAXCHARLENGTH;

    if(player.currRoom->itemList==NULL){
        printf("No Items in this room, please choose another command.\n");
        return;
    }

    while(!itemCanBeTaken((player.currRoom->itemList),userInput)){

        printf("Enter a valid item to pick up.\n");

        getline(&userInput, &inputSize, stdin);
        int cLen = strlen(userInput);
        userInput[cLen-1] = '\0';
        
    }

    ItemNode* swappedItem = dropItem(&(player.currRoom->itemList), userInput);
    ItemNode* newItem = addItem(&(player.inventory),swappedItem);

    printf("You have taken %s.\n", userInput);
}

void dropCommand(){
    
    char* userInput = malloc(sizeof(char) * MAXCHARLENGTH);
    size_t inputSize = MAXCHARLENGTH;

    if(player.inventory==NULL){
        printf("No items in inventory, please choose another command.");
        return;
    }

    
    while(!itemCanBeTaken((player.inventory),userInput)){

        printf("Enter a valid item to drop.\n");

        getline(&userInput, &inputSize, stdin);
        int cLen = strlen(userInput);
        userInput[cLen-1] = '\0';
    }

    ItemNode* swappedItem = dropItem(&(player.inventory), userInput);
    ItemNode* newItem = addItem(&(player.currRoom->itemList),swappedItem);
    printf("You have dropped %s.\n", userInput);

}
_Bool isValidCharacterGuess(char* guess){
    for(int x = 0;x<5;x++){
        if(strcmp(characters[x],guess)==0){
            return true;
        }
    }
    return false;
}
Room* findCharacter(char* characterToFind){
    for(int x = 0;x<9;x++){
        if(strcmp(grid[x].character,characterToFind)==0){
            return &grid[x];
        }
    }
}
void clueCommand(){
    printf("So you think you figured it out?\n");
    char* userInput = malloc(sizeof(char) * MAXCHARLENGTH);
    size_t inputSize = MAXCHARLENGTH;

    char* itemGuess = (char*) malloc(40); // string to store the item guess
    char* characterGuess = (char*) malloc(40); // string to store the character guess
    


    if((player.inventory)==NULL && (player.currRoom->itemList)==NULL){ // the item guess is invalid because there are no valid items
        printf("Cannot make a guess, there must be an item near you or with you! Choose another command.\n");
        return;
    }
    printf("Here's a little reminder of your options:\n");
    listCommand();
        
        while(true){
            printf("Enter valid murder item.\n");
            getline(&userInput, &inputSize, stdin);
            int cLen = strlen(userInput);
            userInput[cLen-1] = '\0';

            if(itemCanBeTaken((player.inventory),userInput) || itemCanBeTaken((player.currRoom->itemList),userInput)){
                strcpy(itemGuess,userInput);
                break;
            }
        }

        
        while (!isValidCharacterGuess(userInput)){
        printf("Enter valid character... murderer\n");
        
        getline(&userInput, &inputSize, stdin);
        int cLen = strlen(userInput);
        userInput[cLen-1] = '\0';
        }

        strcpy(characterGuess,userInput); // save the player's character guess

        Room* location = findCharacter(characterGuess); // find where that character is

        swapCharacter(location,player.currRoom); // swap the character with the current room's character

        _Bool roomMatch = strcmp(player.currRoom->name,murderRoom)==0;
        _Bool characterMatch = strcmp(characterGuess,murderer)==0;
        _Bool itemMatch = strcmp(itemGuess,murderWeapon)==0;

        if(roomMatch && characterMatch && itemMatch){
            gameOver = true;
        }
        if(roomMatch) { // check for room match
            printf("ROOM MATCH!\n");
        }
        if(characterMatch) { // check for character match
            printf("CHARACTER MATCH!\n");
        }
        if(itemMatch) { // check for item match
            printf("ITEM MATCH!\n");
        }
        if(itemMatch || characterMatch || roomMatch){
            printf("Close... Just a couple more details. Keep digging detective!\n");
        }
        else{
            printf("No matches... Get back to work!\n");
        }
        attempts = attempts+1;

}


void handleUserInput(char* userInput){
    if(strcmp(userInput, "help")==0){
        helpTable();
        return;
    }
    else if(strcmp(userInput, "list")==0){
        listCommand();
        return;
    }
    else if(strcmp(userInput, "look")==0){
        lookCommand();
        return;
    }
    else if(strcmp(userInput, "go")==0){
        goCommand();
        return;
    }
    else if(strcmp(userInput, "take")==0){
        takeCommand();
        return;
    }
    else if(strcmp(userInput, "drop")==0){
        dropCommand();
        return;
    }
    else if(strcmp(userInput, "inventory")==0){
        if( player.inventory==NULL){
            printf("Inventory is empty.\n");
        }
        else{
            printf("Inventory: ");
            printElements(player.inventory);
        }
        return;
    }
    else if(strcmp(userInput, "clue")==0){
        clueCommand();
        return;
        
    }
    else if(strcmp(userInput,"hint")==0){
        printf("SHHHH... this is a secret.... but you only have %d attempts left until the murderer gets you!....\n", 11-attempts);
    }
    else{
        //size_t inputSize = MAXCHARLENGTH;
        printf("Invalid command. Type command help to get list of valid commands\n");
        return;
        //getline(&userInput, &inputSize, stdin);
    
    }
}
////////////////// Game loop //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    char* userInput = malloc(sizeof(char) * MAXCHARLENGTH);
    size_t inputSize = MAXCHARLENGTH;
    printf("Welcome to Clue! There has been a murder somewhere in the map. We need your help finding who has done it, where they did it, and what they used to it with.\nUse the command help to lookup commands.\n");
    // printf("%s\n", murderWeapon);
    // printf("%s\n", murderer);
    // printf("%s\n", murderRoom);
    while(!gameOver){ //while the game is not over run game logic

        getline(&userInput, &inputSize, stdin);
        int cLen = strlen(userInput);
        userInput[cLen-1] = '\0';


        handleUserInput(userInput);

        if(attempts>10){
            gameOver = true;
        }
    }
    attempts > 10 ? printf("You Lost!  %s got you before you solved the case! \n", murderer) : printf("You solved the murder! %s is being handcuffed and taken away.\n", murderer);
    printf("%s commited the murder in the %s with a %s\n", murderer, murderRoom, murderWeapon);

    // free any variables that space was dynamically allocated for
    free(userInput);
    free(grid);
}