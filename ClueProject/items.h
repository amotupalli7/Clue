#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct ItemNode{
  char* itemName; // Name of the item
  struct ItemNode* next; // pointer to the next item
}ItemNode;

ItemNode* addItem(ItemNode** linkedListAddress, ItemNode* itemToAdd); // adds an itemNode to a linkedList given a linkedlist address

ItemNode* dropItem(ItemNode** linkedListAddress, char* target); // assumes that nodeToRemove is in linkedList




