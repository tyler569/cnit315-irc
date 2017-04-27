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

    
    char *word="shit";
    char *nick="Bob";
    char *nnick="tom";
    char *nword="~profanity";
    char *back1, *back2, *back3, *back4, *back5;
    
     	
    back1 = profanity_handler_function(nick, word);
    printf("\n%s\n",back1);

    back2 = profanity_handler_function(nick, word);
    printf("\n%s\n",back2);   
		
    back3 = profanity_handler_function(nick, word);
    printf("\n%s\n",back3);

    back4 = profanity_handler_function(nick, word);
    printf("\n%s\n",back4);

    back5 = profanity_handler_function(NULL, nword);

    
    return 0;
}*/

char *profanity_handler_function(char *nick, char *message) {
    
    /*Variables*/
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
	struct names *keep = list;

        while(keep != NULL){  
        /*if it is a reoccuring nick increment their count*/
           if(strcmp(keep->nick,nick) == 0){
	   keep->count = keep->count + 1;
	   check = false;
	   break;
           } 
	
	keep=keep->next;
	}
	
	/*if it is a new nick add it to the list*/
	if(check==true){

	struct names *temp;
	temp  = (struct names *)malloc(sizeof(struct names));
	strcpy(temp->nick,nick);
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
	quick->next=NULL;
        list = quick;
	}
        
        ret = malloc(512);
        strcpy(ret, line);
    }

    /*if they want to see the list*/
    if(strstr(tmp,"~profanity") != NULL){
	struct names *print;
	print = (struct names *)malloc(sizeof(struct names));
	print = list;
	/*print the list*/
	while(print != NULL){
	printf("Name: %s        Count: %d\n",print->nick,print->count);
	print=print->next;
	}
    }
    /*Return used profanity message, or null*/
    return ret;
}

