
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#define PORT 6667
#define RECV_BUF_LEN 1024

/*
int main(){

    char input[31], *result;
    char *test;

    printf("enter a message\n");

    fgets(input,128,stdin);
    sscanf(input,"%s", &test);

    result = profanity_handler_function(test + 1);

    return 0;
}*/

char *profanity_handler_function(const char *message) {
    char *ret = NULL;
    char *newm = calloc(1, 512);
    char *line = "CNIT BOT is a family friendly bot, please no explicit language";
    int i;

    for (i=0; i<strlen(message); i++) {
        newm[i] = tolower(message[i]);
    }

    if (strstr(newm, " fuck ") != NULL || strstr(newm, " shit ") != NULL ||
        strstr(newm, " ass ") != NULL || strstr(newm, " bitch ") != NULL ||
        strstr(newm, " damn ") != NULL) {

        ret = malloc(512);
        strcpy(ret, line);

    }
    free(newm);
    return ret;
}

