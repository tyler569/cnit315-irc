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

char *reverseHandler(const char *message)
int top = -1;
char rev[MAX];
void push(char element);
int IfFull();
int IfEmpty();
char pop();

char *reverseHandler(const char *input)
{
char * retValue = malloc(512);

if(strncmp(input, "~reverse ", 9) ==0){

for(count = 0; count < strlen(rev); count++)
{
push(rev[count]);
}
for(count = 0; count < strlen(rev); count++)
{
rev[count] = pop();
}
strcpy(ret,rev);
}

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

