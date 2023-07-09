#include <stdio.h>


typedef struct Room{
  char* name;
  struct Room* North;
  struct Room* South;
  struct Room* East;
  struct Room* West;
  struct ItemNode* itemList; // linked list of items
  char* character; // string character in the room
} Room;

 

void swapCharacter(Room* room1, Room* room2); // will swap characters given two Room pointers




