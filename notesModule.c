#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#define MAXLEN 512
#define MAXNICK 32

struct noteNode;
char * notesModuleHandler(char *, const char *);
time_t rawTime;
void newNote(const char *, char *);
char * searchNotes(const char *);
char * printNote(struct noteNode *);
void delNote(char *, const char *, int);
int noteCounter = 0;

struct noteNode {
    int noteNum;
    char userName[MAXNICK];
    char text[MAXLEN];
    struct tm * timeStamp;
    struct noteNode * nextNote;
};

static struct noteNode * head = NULL;

/* Receives all messages from the irc channel
 * Converts into a note if the message contains
 * ~note add 
 *
 * Searches for notes created by a specific nickname
 * with ~note search <nick>
 *
 * Deletes individual user notes associated with a nickname
 */
char *notesModuleHandler(char * nick, const char * input){
    char * retValue = malloc(512);

    if(strncmp(input, "~note add ", 10) == 0){
        newNote(input + 10, nick);
        strcpy(retValue, "New Note Added!");
    }else if(strncmp(input, "~note search ", 13) == 0){
        
        if(strncmp(input, "~note search me", 15) == 0){
            retValue = searchNotes(nick);
        }else{
            retValue = searchNotes(input + 13);
        }

    }else if(strncmp(input, "~note del ", 10) == 0){
        
        if(strncmp(input, "~note del all", 13) == 0){ 
            delNote(nick, input, 1);
            strcpy(retValue, "All user notes deleted.");
        }else{
            delNote(nick, input, 0);
            strcpy(retValue, "Note deleted.");
        }

    }else if(strncmp(input, "~note", 5) == 0){ 
        strcpy(retValue, "Note command format: ~note <add, search [me], del [all] [num]> [note]");
    }else{
        strcpy(retValue, "Note command format: ~note <add, search [me], del [all] [num]> [note]");
    }   

    return retValue;
}

void delNote(char * nick, const char * input, int wipe){
    
    struct noteNode * current = head;
    struct noteNode * previous = head;
    
    if(wipe == 0){
        while(current != NULL){
            if(strcmp(nick, current -> userName) == 0){
                if(head == current){
                    head = current -> nextNote;
                }else{
                    previous -> nextNote = current -> nextNote;
                }
                break;
            }
            previous = current;
            current = current -> nextNote;
        }
    }else if(wipe == 1){
        while(current != NULL){
            if(strcmp(nick, current -> userName) == 0){
                if(head == current){
                    head = current -> nextNote;
                }else{
                    previous -> nextNote = current -> nextNote;
                }
            }
            previous = current;
            current = current -> nextNote;
        }
    }
}

/* Function to search for notes associated with usernames */
char * searchNotes(const char * searching){
    struct noteNode * current = head;

    while(current != NULL){
        if(strcmp(searching, current -> userName) == 0){
            return(printNote(current));
        }

        current = current -> nextNote;
    }
    
    return NULL;
}

/* Function for to create new notes */
void newNote(const char * note, char * usrName){
    noteCounter ++;
    struct noteNode * newNoteNode = calloc(1, sizeof(struct noteNode));

    newNoteNode -> noteNum = noteCounter;
    strcpy(newNoteNode -> text, note);
    strcpy(newNoteNode -> userName, usrName);
   
    time (&rawTime);
    newNoteNode -> timeStamp = localtime ( &rawTime );

    newNoteNode -> nextNote = head;
    head = newNoteNode;
}

char * printNote(struct noteNode * printMe){
    char * result = malloc(512);

    sprintf(result, "%i. %s %s: %s\n", 
                printMe -> noteNum, asctime(printMe -> timeStamp), printMe -> userName, printMe -> text);
    
    return result;
}
