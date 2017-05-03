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

#define PORT 6667
#define RECV_BUF_LEN 1024
#define MAX 500

int element;
int top = -1;
char rev[MAX];
void push(char element);
int IfFull();
int IfEmpty();
char pop();

/*
int  main()
{
    char rev[] = "this is a test.";
    int count;
    for(count = 0; count < strlen(rev); count++)
    {
        push(rev[count]);
    }
    for(count = 0; count < strlen(rev); count++)
    {
        rev[count] = pop();
    }
    printf("%s \n", rev);
}*/

void push(char element)
{
    if(IfFull())
    {
        printf("Stack Overflow Error");
    }
    else
    {
        top = top + 1;
        rev[top] = element;
    }
}

char pop()
{
    if(IfEmpty())
    {
        printf("Stack is empty");
        return 1;
    }
    else
    {
        element = rev[top];
        top =  top - 1;
        return element;
    }
}

int IfEmpty()
{
    if(top == -1)
        return 1;
    else
        return 0;
}
int IfFull()
{
    if (top == MAX-1)
        return 1;
    else
        return 0;
}

char *reverse_handler(const char *message) {
    char *ret = calloc(1, 512);
    int i;
    int j = 0;

    if (strncmp(message, "~reverse", 8) != 0) {
        return NULL;
    }
    for (i=strlen(message) - 3; i>9; i--) {
        ret[j++] = message[i];
    }
    return ret;
}

