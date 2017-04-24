#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include "ircutils.h"
#define MAXLEN 512
#define MAXNICK 32

/* ircsend(0, # strings concatenating) */
/* irc_send(0, 4, "PRIVMSG ", channel, " :", message_out); */


struct noteNode;
char * notesModuleHandler(char *, const char *);
time_t rawTime;
void newNote(const char *, char *);
char * searchNotes(const char *);
char * printNote(struct noteNode *);
char * removeNewLine(char *);
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
    char * retValue;

    if(strncmp(input, "~note add ", 10) == 0){
        retValue= malloc(512);
        newNote(input + 10, nick);
        return retValue;
    }else if(strncmp(input, "~note search ", 13) == 0){
        retValue= malloc(512);

        if(strncmp(input, "~note search me", 15) == 0){
            retValue = searchNotes(nick);
        }else{
            retValue = searchNotes(input + 13);
        }

        return retValue;

    }else if(strncmp(input, "~note del ", 10) == 0){
        retValue= malloc(512);

        if(strncmp(input, "~note del all", 13) == 0){ 
            delNote(nick, input, 1);
        }else{
            delNote(nick, input + 10, 0);
        }
        return retValue;

    }else if(strncmp(input, "~note", 5) == 0){ 
        retValue= malloc(512);
        strcpy(retValue, "Note command format: ~note <add, search [me] [num] [nick], del [all] [num]> [note]");
        return retValue;
    }else{
        return NULL;
    }   

}

void delNote(char * nick, const char * input, int wipe){

    struct noteNode * current = head;
    struct noteNode * previous = head;
    long searchIndex = strtol(input, (char **)NULL, 10);
    
    if(wipe == 0){
        if(searchIndex > 0){
            while(current != NULL){
                if(strcmp(nick, current -> userName) != 0 && (searchIndex == current -> noteNum)){
                    irc_send(0, 4, "PRIVMSG ", channel, " :", "That's not your note! Hands off! >:(");
                } 

                if(strcmp(nick, current -> userName) == 0 && (searchIndex == current -> noteNum)){
                    irc_send(0, 4, "PRIVMSG ", channel, " :", "Note deleted");
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
        irc_send(0, 4, "PRIVMSG ", channel, " :", "All user notes deleted.");
    }
}

/* Function to search for notes associated with usernames */
char * searchNotes(const char * searching){
    struct noteNode * current = head;
    const char * tempSearch = searching;/*removeNewLine(searching);*/
    long searchIndex = strtol(searching, (char **)NULL, 10);
    int found = 0;
    if(searchIndex <= 0){
        while(current != NULL){
            if(strcmp(searching, current -> userName) == 0 || strcmp(tempSearch, removeNewLine(current -> userName)) == 0){
                found = 1;
                irc_send(0, 4, "PRIVMSG ", channel, " :", printNote(current));
            }
            
            current = current -> nextNote;
        }
    }else if(searchIndex > 0){ 
        while(current != NULL){
            if(searchIndex == current -> noteNum){
                found = 1;
                irc_send(0, 4, "PRIVMSG ", channel, " :", printNote(current));
            }

            current = current -> nextNote;
        }
    }
    
    if(found == 0){
        irc_send(0, 4, "PRIVMSG ", channel, " :", "No notes found, sorry! :(");
    }

    return NULL;
}

/* Function for to create new notes */
void newNote(const char * note, char * usrName){
    struct noteNode * newNoteNode = calloc(1, sizeof(struct noteNode));
    noteCounter ++;

    newNoteNode -> noteNum = noteCounter;
    strcpy(newNoteNode -> text, note);
    strcpy(newNoteNode -> userName, usrName);

    time (&rawTime);
    newNoteNode -> timeStamp = localtime ( &rawTime );

    newNoteNode -> nextNote = head;
    head = newNoteNode;
    irc_send(0, 4, "PRIVMSG ", channel, " :", "New Note added!");
}

char * printNote(struct noteNode * printMe){
    char * result = malloc(512);

    sprintf(result, "%i. (%s) %s: %s\n", 
            printMe -> noteNum, removeNewLine(asctime(printMe -> timeStamp)),
            printMe -> userName, printMe -> text);
    return result;
}

char * removeNewLine(char * buf){
     char *pos;
     if((pos=strchr(buf, '\n')) != NULL)
             *pos = '\0';

     return buf;
}

/* Kill dis once done testing 
int main(){
    char * foo = "~note add bananas are fruit";
    char * bar = "MobiusOne";
    char * baz = NULL;
    baz = notesModuleHandler(bar, foo);
    
    notesModuleHandler("Meh", "~note add oranges are fruit");
    notesModuleHandler("Jenkins", "~note add vegetables are not fruit");
    notesModuleHandler("MobiusOne", "~note add hey its me Mobius");
    notesModuleHandler("Doom Van Doorne", "~note add I am become fruit");
    notesModuleHandler("Jenkins", "~note add vegetables are sometimes fruit");
    notesModuleHandler("Jenkins", "~note add Not actually though");
    notesModuleHandler("Doom Van Doorne", "~note add Get down here! Not fair if I have all the fun!");

    baz = notesModuleHandler("MobiusOne", "~note search 5");
    
    printf("%s", baz);

    return 0;
} */
