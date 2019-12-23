#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

typedef struct node {
    char *artist;
    char *songName;
    char *genre;
    struct node *next;
} Node;

void inputStringFromUser(char *prompt, char *s, int arraySize);
Node *createNode(void);
bool isEmpty(Node *head);
void printList(Node *head);
Node *insertSong(Node *head);
void searchSong(Node *head);
Node *deleteNode(Node *head);
Node *deleteAllNodes(Node *head);
Node *sorting(Node *head);

const int MAX_LENGTH = 1024;

int main(void) {
    Node *head = NULL;
 
    // Announce the start of the program
    printf("Personal Music Library.\n\n");
    printf("%s", "Commands are I (insert), D (delete), S (search by song name),\n"
           "P (print), Q (quit).\n");

    char response;
    char input[MAX_LENGTH + 1];
    do {
        inputStringFromUser("\nCommand", input, MAX_LENGTH);
        response = toupper(input[0]);

        if (response == 'I') {
            head = insertSong(head);
        } else if (response == 'D') {
            head = deleteNode(head);
        } else if (response == 'S') {
            searchSong(head);
        } else if (response == 'P') {
            printList(head);
        } else if (response == 'Q') {

        } else {
            printf ("\nInvalid command.\n");
        }
    } while (response != 'Q');
    
    //deleting all nodes before quitting
    head = deleteAllNodes(head);
    
    return 0;
}

void inputStringFromUser(char *prompt, char *s, int maxStrLength) {
    int i = 0;
    char c;

    printf("%s --> ", prompt);
    while (i < maxStrLength && (c = getchar()) != '\n')
        s[i++] = c;
    s[i] = '\0';
}

Node *createNode(void) {
    Node *newNode = (Node *) malloc((sizeof(Node))*MAX_LENGTH);
    
    char *inputSongName, *inputArtist, *inputGenre;
    
    inputSongName = (char*)malloc(sizeof(char)*(MAX_LENGTH+1));
    inputArtist = (char*)malloc(sizeof(char)*(MAX_LENGTH+1));
    inputGenre = (char*)malloc(sizeof(char)*(MAX_LENGTH+1));
    
    inputStringFromUser("Song name", inputSongName, MAX_LENGTH);
    newNode->songName = inputSongName;
          
    inputStringFromUser("Artist", inputArtist, MAX_LENGTH);
    newNode->artist = inputArtist;
        
    inputStringFromUser("Genre", inputGenre, MAX_LENGTH);
    newNode->genre = inputGenre;
        
    newNode->next = NULL;
        
    return newNode;
}

bool isEmpty(Node *head) {
    if (head == NULL) {
        return true;
    }
    
    return false;
}

void printList(Node *head) {
    Node *n = head;
    
    if (isEmpty(n)) {
        
        printf("\nThe music library is empty.\n");
        
    } else {
        
        printf("My Personal Music Library:\n\n");

        while (n != NULL) {
            //print out the elements in order
            printf("\n");
            printf("%s\n", n->songName);
            printf("%s\n", n->artist);
            printf("%s\n", n->genre);
            printf("\n");
            
            n = n->next;
        }
    
    }
}

Node *insertSong(Node *head) {//fixed v1
    
    if (isEmpty(head)) {
        return createNode();
    } 
    
    //creating new node
    Node *newNode = createNode();
    
    //checking is the song is a duplicate
    if (strcmp(newNode->songName, head->songName) == 0) {//checking if head is the same song inserted
        printf("\nA song with the name '%s' is already in the music library.\n"
                "No new song entered.\n", newNode->songName);
        
        free(newNode->songName);
        free(newNode->artist);
        free(newNode->genre);
        free(newNode);
        
        return head;
    }
    
    Node *tempHead = head;
    while (tempHead->next != NULL && strcmp(newNode->songName, tempHead->songName) != 0) {//checking the rest if same song song inserted
        tempHead = tempHead->next; 
        
        if (strcmp(newNode->songName, tempHead->songName) == 0) {
            printf("\nA song with the name '%s' is already in the music library.\n"
                    "No new song entered.\n", newNode->songName);
                    
            free(newNode->songName);
            free(newNode->artist);
            free(newNode->genre);
            free(newNode);
            
            return head;
        }
    }
    
    //inserting a node
    if (strcmp(head->songName,newNode->songName) > 0){ //When new song is to be entered before head 
        newNode->next=head;
        head=newNode;
        return head;
    }
    
    tempHead = head; //resetting temphead for inserting
    
    while (tempHead->next != NULL && strcmp(tempHead->next->songName, newNode->songName) <= 0) {//checking the rest if same song song inserted
        tempHead = tempHead->next;
    }
    
    newNode->next = tempHead->next;
    tempHead->next = newNode;
    
    return head;
}

void searchSong(Node *head) {
    bool songFound = false;
    Node *tempHead = head;
    
    char *inputSongName;
    inputSongName = (char*)malloc(sizeof(char)*(MAX_LENGTH+1));

    inputStringFromUser("\nEnter the name of the song to search for", inputSongName, MAX_LENGTH);
    
    if (strcmp(tempHead->songName, inputSongName) == 0) {//checking head
        songFound = true;
    }
    
    while (songFound == false && strcmp(tempHead->songName, inputSongName) != 0 && tempHead->next != NULL) {//checking the rest
        tempHead = tempHead->next; 
        
        if (strcmp(tempHead->songName, inputSongName) == 0)
            songFound = true;
    }
    
    if (songFound) {
        printf("The song name '%s' was found in the music library.\n\n", inputSongName);
        printf("%s\n", tempHead->songName);
        printf("%s\n", tempHead->artist);
        printf("%s\n", tempHead->genre);
    } else {
        printf("\nThe song name '%s' was not found in the music library.\n", inputSongName);
    }
} 

Node *deleteNode(Node *head) {
    
    char *inputSongName;
    inputSongName = (char*)malloc(sizeof(char)*(MAX_LENGTH+1));
    
    inputStringFromUser("\nEnter the name of the song to be deleted", inputSongName, MAX_LENGTH);
    
    if (isEmpty(head)) { //nothing to do
        printf("\nThe song name '%s' was not found in the music library.\n",inputSongName);
        return head;
    }
    
    if (strcmp(head->songName, inputSongName) == 0) {//checking head
        
        printf("\nDeleting a song with name '%s' from the music library.\n", inputSongName);
        
        free(head->songName);
        free(head->artist);
        free(head->genre);
        
        head=head->next;
        
        return head;
    }
    
    Node *tempHead = head;
        
    while (strcmp(tempHead->next->songName, inputSongName) != 0 && tempHead->next != NULL) {//checking the rest
        tempHead = tempHead->next; 
        if (tempHead->next == NULL) {
            printf("\nThe song name '%s' was not found in the music library.\n",inputSongName);
            return head;
        }
    }
        
    printf("\nDeleting a song with name '%s' from the music library.\n", inputSongName);    
    free(tempHead->next->songName);
    free(tempHead->next->artist);
    free(tempHead->next->genre);
        
    tempHead->next=tempHead->next->next;
        
    return head;
}

Node *deleteAllNodes(Node *head) {
    printf("\n");
    
    while (head != NULL) {
        printf("Deleting a song with name '%s' from the music library.\n\n", head->songName);
        
        free(head->songName);
        free(head->artist);
        free(head->genre);
        
        head=head->next;
    }
    
    printf("The music library is empty.\n\n");
    
    return head;
}