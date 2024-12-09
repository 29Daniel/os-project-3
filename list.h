#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct node {
   char username[30];
   int socket;
   struct node *next;
};

struct room {
    char name[30];             // Room name
    struct node *users;        // Linked list of users in the room
    struct room *next;         // Pointer to the next room
};

/////////////////// USERLIST //////////////////////////

//insert node at the first location
struct node* insertFirstU(struct node *head, int socket, char *username);

//find a node with given username
struct node* findU(struct node *head, char* username);



/////////////////// ROOMLIST //////////////////////////

struct room *createRoom(char *name);
void removeRoom(struct room **head, char *name);