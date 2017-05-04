
/*
 * CNIT315 FINAL PROJECT
 *
 * file by Tyler Philbrick
 *
 * Base IRC Connection and test handler
 */

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
#include <assert.h>
#include <ctype.h>

#include "ircutils.h"
#include "modules.h"

#define PORT 6667
/* Has to be >= 512 per IRC spec */
#define RECV_BUF_LEN 1024

char *example_handler_function(const char *message);

char *address = "irc.freenode.net";
char *channel = "#cnit315_bot_test";
char *nickname = "test_bot_315";

int socket_fd = 0;

char *nick(const char *message) {
    char *nick;
    char *nick_end;

    if (message[0] == ':') {
        if (strchr(message, ' ') < strchr(message, '!')) {
            return NULL;
        }
        if ((nick_end = strchr(message, '!')) != NULL) {
            nick = calloc(1, 32);
            memcpy(nick, message + 1, nick_end - message - 1);
            return nick;
        } else {
            return NULL;
        }
    } else {
        return NULL;
    }
}

char *command(const char *message) {
    char *command = calloc(1, 32);
    char *command_start;
    char *command_end;

    if (message[0] == ':') {
        if ((command_start = strchr(message, ' ')) != NULL) {
            if ((command_end = strchr(command_start + 1, ' ')) != NULL) {
                memcpy(command, command_start + 1, command_end - command_start - 1);
                return command;
            } else {
                strcpy(command, command_start + 1);
                return command;
            }
        }
    } else {
        command_end = strchr(message, ' ');
        memcpy(command, message, command_end - message);
        return command;
    }
    return "";
}

int main(int argc, char *argv[]) {
    int sock, numbytes;
    char *message;
    char *message_out;
    int buf_index = 0;
    int buf_remain;
    char buf[RECV_BUF_LEN + 1]; /* +1 just in case, I think its possible to overrun */
    char save, save2, save3;
    struct hostent *host;
    struct sockaddr_in remote_addr;

    if ((host = gethostbyname(address)) == NULL) {
        perror("gethostbyname()");
        exit(1);
    }

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket()");
        exit(1);
    }

    socket_fd = sock;

    remote_addr.sin_family = AF_INET;

    remote_addr.sin_port = htons(PORT);
    remote_addr.sin_addr = *((struct in_addr *)host->h_addr);

    memset(&(remote_addr.sin_zero), 0, 8);

    if (connect(sock, (struct sockaddr *)&remote_addr, sizeof(struct sockaddr)) == -1) {
        perror("connect()");
        exit(1);
    }

    /* For now, I just assume send() works, we can change this if we want */
    irc_send(sock, 4, "USER ", nickname, " 0 * :", nickname);
    irc_send(sock, 2, "NICK ", nickname);
    irc_send(sock, 2, "JOIN ", channel);

    while (1) {
        buf_remain = RECV_BUF_LEN - buf_index;

        if ((numbytes = recv(sock, buf + buf_index, buf_remain, 0)) == -1) {
            perror("recv()");
            exit(1);
        }
        buf_index += numbytes;

        while ((message = strchr(buf, '\n')) != NULL) {
            /* OVERLOADING numbytes */
            numbytes = message - buf + 1;

            save = buf[numbytes];
            save2 = buf[numbytes - 1];
            save3 = buf[numbytes - 2];
            buf[numbytes] = '\0';
            buf[numbytes - 1] = '\0';
            buf[numbytes - 2] = '\0';

            printf(">> %s\n", buf);

            if (strncmp(buf, "PING", 4) == 0) {
                irc_send(sock, 2, "PONG ", &buf[5]);
            }

            if ((message = strchr(buf, ' ')) != NULL) {
                if (strncmp(message + 1, "376", 3) == 0) {
                    irc_send(sock, 2, "JOIN ", channel);
                }
            }

            if (strcmp(command(buf), "PRIVMSG") == 0) {
  		        message_out = profanity_handler_function(nick(buf), message + 1);
                if (message_out != NULL) {
                    irc_send(sock, 4, "PRIVMSG ", channel, " :", message_out);
                    free(message_out);
                }
            }

            if ((message = strchr(&buf[1], ':')) != NULL) {

                /* This is the code that hooks into your handlers */
                /* See below for implementation of example */

                message_out = example_handler_function(message + 1);
                if (message_out != NULL) {
                    irc_send(sock, 4, "PRIVMSG ", channel, " :", message_out);
                    free(message_out);
                }
                message_out = notesModuleHandler(nick(buf), message + 1);
                if (message_out != NULL) {
                    irc_send(sock, 4, "PRIVMSG ", channel, " :", message_out);
                    free(message_out);
                }
                message_out = Time_Handler(command(buf), nick(buf), message + 1);
                if (message_out != NULL) {
                    irc_send(sock, 4, "PRIVMSG ", channel, " :", message_out);
                    free(message_out);
                }
                message_out = reverse_handler(message + 1);
                if (message_out != NULL) {
                    irc_send(sock, 4, "PRIVMSG ", channel, " :", message_out);
                    free(message_out);
                }
 
                /* repeat for each handler */
            } else {
                message_out = Time_Handler(command(buf), nick(buf), "");
                if (message_out != NULL) {
                    irc_send(sock, 4, "PRIVMSG ", channel, " :", message_out);
                    free(message_out);
                }
            }

            buf[numbytes] = save;
            buf[numbytes - 1] = save2;
            buf[numbytes - 2] = save3;
            memmove(buf, buf + numbytes, RECV_BUF_LEN - numbytes);
            buf_index -= numbytes;
            /* printf("index: %i, numbytes: %i, buf: %s, buf: %p\n", buf_index, numbytes, buf, buf); */

            memset(buf + buf_index, 0, RECV_BUF_LEN - buf_index);
        }
    }

    close(sock);
    return 0;
}

void irc_send(int sock, int count, ...) {
    int i;
    va_list v;

    if (sock == 0) {
        sock = socket_fd;
    }

    va_start(v, count);
    printf("<< ");

    for (i=0; i<count; i++) {
        char *buf = va_arg(v, char *);
        send(sock, buf, strlen(buf), 0);
    }
    va_end(v);

    send(sock, "\r\n", 2, 0);
    printf("\n");
}

/* Following is an example of the kind of 'main' function you should
 * write for your parts.  You can have as many helper functions called
 * from this function as you want.
 *
 * Please do your part in a seperate .c file in this directory,
 * we can link it all together and everything will be more organized.
 *
 * This is the only function you need to worry about, this this same
 * funtion signature,
 *
 * char *xyz_handler(const char *message)
 *
 * and be sure to return a point your got from malloc.
 * you won't be able to return local strings anyway, so just standardizing
 * on a malloc()'d string makes it easier for me to free the memory and
 * lowers our chances of leaking like the Titanic.
 *
 * Do let me know if you have any questions, comments, or concerns.
 *
 * -Tyler
 *
 */

char *example_handler_function(const char *message) {
    char *ret = NULL;
    if (strncmp(message, "~test", 5) == 0) {
        ret = malloc(512);
        strcpy(ret, "Test successful");
    }
    return ret;
}

