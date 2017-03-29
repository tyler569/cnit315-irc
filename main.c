
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define RECV_BUF_LEN 1024

int main() {

    int sock = 0;
    int err;
    char recv[RECV_BUF_LEN];
    int n;

    struct sockaddr_in server_addr;
    struct hostent *server;

    memset(recv, 0, sizeof(recv));

    /* @configuration */
    server = gethostbyname("irc.freenode.net");
    if (server == NULL) {
        printf("Error: [%s]\n", strerror(errno));
        exit(0);
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        printf("Error: [%s]\n", strerror(errno));
        exit(0);
    } 

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    memcpy(server->h_addr, &server_addr.sin_addr.s_addr, server.h_length);
    server_addr.sin_port = htons(6667);

    err = connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (err < 0) {
        printf("Error: [%s]\n", strerror(errno));
        exit(0);
    }
    
    while ((n = read(sock, recv, RECV_BUF_LEN-1)) > 0) {
        recv[n] = 0;
        printf(">> %s", recv);
    }

    exit(0);
}

