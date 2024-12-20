#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h> // For thread synchronization

// Structure representing a user
struct node {
    char username[30];
    int socket;
    struct node *next;
};

// Structure representing a chatroom
struct room {
    char name[30];             // Room name
    struct node *users;        // Linked list of users in the room
    struct room *next;         // Pointer to the next room in the list
};

// Global mutexes for thread-safe access
pthread_mutex_t user_mutex;
pthread_mutex_t room_mutex;

/////////////////// USERLIST //////////////////////////

// Insert a new user into the linked list at the first location
struct node* insertFirstU(struct node *head, int socket, char *username);

// Search for a user by username in the linked list
struct node* findU(struct node *head, char* username);

// Remove a user from the user list
void removeUser(struct node **head, int socket);

/////////////////// ROOMLIST //////////////////////////

// Create a new chat room
struct room *createRoom(char *name);

// Find a room by name
struct room *findRoom(struct room *head, char *name);

// Remove a chat room
void removeRoom(struct room **head, char *name);

// Add a user to a room
void addUserToRoom(struct room *room, struct node *user);

// Remove a user from a room
void removeUserFromRoom(struct room *room, struct node *user);

#endif // LIST_H
