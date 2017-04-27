#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#define PORT 6667
#define RECV_BUF_LEN 1024


    struct names {char *nick; int count; struct names *next;};
    struct names *list;
    char *profanity_handler_function(char *,char *); 


/*int main(){

    
    char *word="SHIT";
    char *nick="Bob";
    char *nnick="tom";
    char *nword="~profanity";
    char *back1, *back2, *back3, *back4, *back5;
    
     	
    back1 = profanity_handler_function(nnick, word);
    printf("\n%s\n",back1);
word = "SHIT";
    back2 = profanity_handler_function(nick, word);
    printf("\n%s\n",back2);   
word = "SHIT";	
    back3 = profanity_handler_function(nnick, word);
    printf("\n%s\n",back3);
word = "SHIT";
    back4 = profanity_handler_function(nick, word);
    printf("\n%s\n",back4);
word = "SHIT";
    back5 = profanity_handler_function(NULL, nword);

    return 0;
}*/

char *profanity_handler_function(char *nick, char *message) {
    
    /*Variables*/
    struct names *keep;
    keep = (struct names *)malloc(sizeof(struct names));
    bool check = true; 
    char *ret = NULL;
    char *newm;
    char *line = "CNIT BOT is a family friendly bot, please no explicit language \n";
    char tmp[100];

    /*put char * into char[]*/
    strcpy(tmp,message);

    /*turn message to all lower case*/
    for(newm = tmp; *newm != '0'; newm++){
       *newm = tolower(*newm);
    }

    /*See if it is Profanity*/
    if (strstr(tmp, "fuck") != NULL || strstr(tmp, "shit") != NULL ||
        strstr(tmp, " ass ") != NULL || strstr(tmp, "bitch") != NULL ||
        strstr(tmp, "damn") != NULL) {
   
	 /*If there have been other profane words*/
	if(list!=NULL){
        /*new pointer to traverse the list*/
	keep = list;
        while(list!=NULL){  
        /*if it is a reoccuring nick increment their count*/
           if(strcmp(list->nick,nick) == 0){
	   list->count = list->count + 1;
	   check = false;
	   break;
           } 
	
	list=list->next;
	}
	list = keep;
		
	/*if it is a new nick add it to the list*/
	if(check==true){
	struct names *temp;
	temp  = (struct names *)malloc(sizeof(struct names));
	temp->nick = nick;
	temp->count = 1;
	temp->next = list;
	list = temp;
	
	}

	}
	/*if the list is empty, start the list*/
	if(list == NULL){ 

	struct names *quick;
	quick = (struct names *)malloc(sizeof(struct names));
	quick->nick=nick;
	quick->count=1;
	quick->next=0;
        list = quick;
	
	}
        
        ret = malloc(512);
        strcpy(ret, line);
    }

    /*if they want to see the list*/
    if(strstr(tmp,"~profanity") != NULL){
	keep = list;
	/*print the list*/
	while(list != NULL){
	printf("Name: %s        Count: %d\n",list->nick,list->count);
	list=list->next;
	}
	list = keep;
	
    }
    /*Return used profanity message, or null*/
    return ret;
}

