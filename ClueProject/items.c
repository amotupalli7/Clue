#include "items.h"
#include <string.h>


struct ItemNode* initializeNode(char* itemName){ // function to create an ItemNode struct pointer given a "string" itemName
	
		ItemNode* xNode = (ItemNode *) calloc(1,sizeof(ItemNode));
		xNode->itemName = itemName;
		xNode->next = NULL;
		return xNode;
}
ItemNode* addItem(ItemNode** linkedListAddress, ItemNode* itemToAdd){ 


	itemToAdd->next = *linkedListAddress;
	*linkedListAddress = itemToAdd;
	
	return itemToAdd;
}

ItemNode* dropItem(ItemNode** linkedListAddress, char* target){

	ItemNode* targetNode = (ItemNode *) calloc(1,sizeof(ItemNode));

	ItemNode* temp = *linkedListAddress;
	ItemNode* prev = NULL;
	// if the target is first in the linked list
	if(strcmp(temp->itemName,target)==0){
		targetNode = temp;
		*linkedListAddress = temp->next;
		
		return targetNode;	
	}
	prev = temp;
	temp = temp->next;
	while(temp!=NULL){

		if(strcmp(temp->itemName,target)==0){// if the target is in the end of the linked list or the middle
			targetNode = temp;
			prev->next = temp->next;
			
			return targetNode;
		}
		prev = temp;
		temp = temp->next;
	}
	// if the target is in the middle
}

void printElements(ItemNode* head){ // prints all elements in a linkedlist given a head pointer
	ItemNode *temp = head;
	while(temp != NULL) {
  		printf("%s   ",temp->itemName);
  		temp = temp->next;
	}
	printf("\n");
}
