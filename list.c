#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"

//insert link at the first location
struct node* insertFirstU(struct node *head, int socket, char *username) {
    
   if(findU(head,username) == NULL) {
           
       //create a link
       struct node *link = (struct node*) malloc(sizeof(struct node));

       link->socket = socket;
       strcpy(link->username,username);
       
       //point it to old first node
       link->next = head;

       //point first to new first node
       head = link;
 
   }
   else
       printf("Duplicate: %s\n", username);
   return head;
}

//find a link with given user
struct node* findU(struct node *head, char* username) {

   //start from the first link
   struct node* current = head;

   //if list is empty
   if(head == NULL) {
      return NULL;
   }

   //navigate through list
    while(strcmp(current->username, username) != 0) {
	
      //if it is last node
      if(current->next == NULL) {
         return NULL;
      } else {
         //go to next link
         current = current->next;
      }
   }      
	
   //if username found, return the current Link
   return current;
}  

// Room Functions

// Create a new room
struct room *createRoom(char *name) {
    struct room *newRoom = (struct room *)malloc(sizeof(struct room));
    if (!newRoom) {
        perror("Failed to allocate memory for new room");
        return NULL;
    }
    strcpy(newRoom->name, name);
    newRoom->users = NULL;
    newRoom->next = NULL;
    return newRoom;
}

// Remove a room from the linked list
void removeRoom(struct room **head, char *name) {
    if (*head == NULL) return;

    struct room *current = *head;
    struct room *prev = NULL;

    // Search for the room
    while (current != NULL && strcmp(current->name, name) != 0) {
        prev = current;
        current = current->next;
    }

    // Room not found
    if (current == NULL) {
        printf("Room '%s' not found.\n", name);
        return;
    }

    // Remove the room
    if (prev == NULL) {
        // Removing the head
        *head = current->next;
    } else {
        prev->next = current->next;
    }

    // Free the memory
    free(current);
    printf("Room '%s' removed successfully.\n", name);
}