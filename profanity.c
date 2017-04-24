#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#define PORT 6667
#define RECV_BUF_LEN 1024


int main(){

    char input[31];
    char *test = "HELLO WORLD";
    char *new;
    char var[20];
    strcpy(var, test);
        	
    printf("\n%s\n", var);

    for(new = var; *new != '\0'; new++){

       *new = tolower(*new);
    }

    printf("\n%s\n", var);

    if(strstr(var, "hello") != NULL){

       printf("\nIT WORKS\n");
    } 

    return 0;
}

char *profanity_handler_function(const char *message) {
    char *ret = NULL;
    char *newm;
    char *line = "CNIT BOT is a family friendly bot, please no explicit language";
    char tmp[100];
    strcpy(tmp,message);

    for(newm = tmp; *newm != '0'; newm++){
       *newm = tolower(*newm);
    }

    if (strstr(tmp, "fuck") != NULL || strstr(tmp, "shit") != NULL ||
        strstr(tmp, "ass") != NULL || strstr(tmp, "bitch") != NULL ||
        strstr(tmp, "damn") != NULL) {

        ret = malloc(512);
        strcpy(ret, line);

    }
    return ret;
}

