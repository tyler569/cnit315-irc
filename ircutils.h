
#ifndef _IRCUTILS_H
#define _IRCUTILS_H

extern char *address;
extern char *channel;
extern char *nickname;

extern int socket_fd;

void irc_send(int, int, ...);

#endif

