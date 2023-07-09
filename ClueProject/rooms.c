
#include "rooms.h"

void swapCharacter(Room* room1, Room* room2){

    char* temp = room1->character;
    room1->character = room2->character;
    room2->character = temp;
    
}