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

void profanity_handler_function(char *message);

int main(){

char input[31], *test;

printf("enter a message\n");

fgets(input,128,stdin);
sscanf(input,"%s", &test);

profanity_handler_function(test);

return 0;
}

void profanity_handler_function(char *message) {
    char *ret = "just fucking print something";
    if (strncmp(message, "~test", 5) == 0) {
        
        strcpy(ret, "You did ~test!");
    }
    printf("\n%s\n", &ret);
}

