#include "list.h"

// Insert a new user at the beginning of the user list
struct node* insertFirstU(struct node *head, int socket, char *username) {
    pthread_mutex_lock(&user_mutex); // Lock before accessing shared user list

    if(findU(head, username) == NULL) {
        struct node *link = (struct node*) malloc(sizeof(struct node));
        if (!link) {
            perror("Failed to allocate memory");
            pthread_mutex_unlock(&user_mutex);
            return head;
        }
        link->socket = socket;
        strcpy(link->username, username);
        link->next = head;
        head = link;
    } else {
        printf("Duplicate username: %s\n", username);
    }

    pthread_mutex_unlock(&user_mutex);
    return head;
}

// Find a user by username
struct node* findU(struct node *head, char* username) {
    pthread_mutex_lock(&user_mutex);

    struct node* current = head;
    while (current) {
        if (strcmp(current->username, username) == 0) {
            pthread_mutex_unlock(&user_mutex);
            return current;
        }
        current = current->next;
    }

    pthread_mutex_unlock(&user_mutex);
    return NULL;
}

// Remove a user from the user list by their socket
void removeUser(struct node **head, int socket) {
    pthread_mutex_lock(&user_mutex);

    struct node *current = *head;
    struct node *prev = NULL;

    while (current) {
        if (current->socket == socket) {
            if (prev) {
                prev->next = current->next;
            } else {
                *head = current->next;
            }
            free(current);
            pthread_mutex_unlock(&user_mutex);
            return;
        }
        prev = current;
        current = current->next;
    }

    pthread_mutex_unlock(&user_mutex);
}

// Create a new room
struct room *createRoom(char *name) {
    pthread_mutex_lock(&room_mutex);

    struct room *newRoom = (struct room *)malloc(sizeof(struct room));
    if (!newRoom) {
        perror("Failed to allocate memory for new room");
        pthread_mutex_unlock(&room_mutex);
        return NULL;
    }

    strcpy(newRoom->name, name);
    newRoom->users = NULL;
    newRoom->next = NULL;

    pthread_mutex_unlock(&room_mutex);
    return newRoom;
}

// Find a room by name
struct room *findRoom(struct room *head, char *name) {
    pthread_mutex_lock(&room_mutex);

    struct room *current = head;
    while (current) {
        if (strcmp(current->name, name) == 0) {
            pthread_mutex_unlock(&room_mutex);
            return current;
        }
        current = current->next;
    }

    pthread_mutex_unlock(&room_mutex);
    return NULL;
}

// Remove a room from the list
void removeRoom(struct room **head, char *name) {
    pthread_mutex_lock(&room_mutex);

    struct room *current = *head;
    struct room *prev = NULL;

    while (current && strcmp(current->name, name) != 0) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Room '%s' not found.\n", name);
        pthread_mutex_unlock(&room_mutex);
        return;
    }

    if (prev == NULL) {
        *head = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
    printf("Room '%s' removed successfully.\n", name);

    pthread_mutex_unlock(&room_mutex);
}

// Add a user to a room
void addUserToRoom(struct room *room, struct node *user) {
    pthread_mutex_lock(&room_mutex);

    if (!room->users) {
        room->users = user;
    } else {
        struct node *current = room->users;
        while (current->next) {
            if (current->socket == user->socket) {
                pthread_mutex_unlock(&room_mutex);
                return; // Avoid duplicates
            }
            current = current->next;
        }
        current->next = user;
    }

    pthread_mutex_unlock(&room_mutex);
}

// Remove a user from a room
void removeUserFromRoom(struct room *room, struct node *user) {
    pthread_mutex_lock(&room_mutex);

    struct node *current = room->users;
    struct node *prev = NULL;

    while (current) {
        if (current->socket == user->socket) {
            if (prev) {
                prev->next = current->next;
            } else {
                room->users = current->next;
            }
            free(current);
            break;
        }
        prev = current;
        current = current->next;
    }

    pthread_mutex_unlock(&room_mutex);
}

