#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#define PORT 6667
#define RECV_BUF_LEN 1024


    struct names {char *nick; int count; struct names *next;};
    struct names *list;
    char *profanity_handler_function(char *,char *); 


int main(){

    
    char *word="shit";
    char *nick="Bob";
    char *nnick="tom";
    char *nword="~profanity";
    char *back;
    
     	
    back = profanity_handler_function(nick, word);
    printf("\n%s\n",back);
    back = profanity_handler_function(nick, word);
    printf("\n%s\n",back);   
    /*back = profanity_handler_function(nnick, word);
    printf("\n%s\n",back);
    back = profanity_handler_function(nnick, word);
    printf("\n%s\n",back);
*/
    back = profanity_handler_function(nick, nword);
     
 
    return 0;
}

char *profanity_handler_function(char *nick, char *message) {
    struct names *keep;
    keep = (struct names *)malloc(sizeof(struct names));
    char *ret = NULL;
    char *newm;
    char *line = "CNIT BOT is a family friendly bot, please no explicit language\n";
    char tmp[100];
    strcpy(tmp,message);

    for(newm = tmp; *newm != '0'; newm++){
       *newm = tolower(*newm);
    }

    if (strstr(tmp, "fuck") != NULL || strstr(tmp, "shit") != NULL ||
        strstr(tmp, " ass ") != NULL || strstr(tmp, "bitch") != NULL ||
        strstr(tmp, "damn") != NULL) {
 
	if(list!=NULL){
	keep=list;
        while(list != NULL){  

        if(strcmp(list->nick,nick) == 0){

	list->count = list->count+1; 
        break; 
        } 
	
	list=list->next;
	}
	list=keep;

	/*struct names *temp;
	temp  = (struct names *)malloc(sizeof(struct names));
	strcpy(temp->nick,nick);
	temp->count = 1;
	temp->next = list;
	list = temp;*/
	}

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
    if(strstr(tmp,"~profanity") != NULL){
	struct names *print;
	print = (struct names *)malloc(sizeof(struct names));
	print = list;
	while(list != NULL){
	printf("Name: %s Count: %d\n",list->nick,list->count);
	list=list->next;
	}
        list=print;
    }
    return ret;
}

