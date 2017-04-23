#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

#define PORT 6667
#define RECV_BUF_LEN 1024

char *profanity_handler_function(const char *message);

int main(){

char input[31], *result;
char *test;

printf("enter a message\n");

fgets(input,128,stdin);
sscanf(input,"%s", &test);

result = profanity_handler_function(test + 1);

return 0;
}

char *profanity_handler_function(const char *message) {
    char *ret = NULL;
    char *newm;
    char *line = "CNIT BOT is a family friendly bot, please no explicit language";
   
    *newm = tolower(*message);

if (strstr(newm, "fuck") != NULL || strstr(newm, "shit") != NULL || strstr(newm, "ass") != NULL || strstr(newm, "bitch") != NULL || strstr(newm, "damn") != NULL) {
        
      ret = malloc(512);
      strcpy(ret, line);

    }
    return ret;
}

