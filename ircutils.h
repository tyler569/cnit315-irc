
#ifndef _IRCUTILS_H
#define _IRCUTILS_H

char *address = "irc.freenode.net";
char *channel = "#cnit315_bot_test";
char *nickname = "test_bot_315";

int socket_fd = 0;

void irc_send(int, int, ...);

#endif

