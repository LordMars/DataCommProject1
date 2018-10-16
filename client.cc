#include <sys/socket.h> /* socket definitions */
#include <sys/types.h> /* socket types */
#include <arpa/inet.h> /* inet (3) funtions */
#include <unistd.h> /* misc. UNIX functions */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
/* Global constants */
#define ECHO_PORT (2002)
#define MAX_LINE (1000)

ssize_t Readline(int sockd, void *vptr, size_t maxlen);
ssize_t Writeline(int sockd, void *vptr, size_t maxlen);

int main(int argc, char *argv[]) {
    if(argc != 6){
        printf("Wrong number of arguments.");
        exit(1);
    }
    char* servIP = argv[1];
    char* servPort = argv[2];
    char* fpath = argv[3];
    char* format = argv[4];
    char* toname = argv[5];
    char* buffer;

    int conn_s;
    int LISTENQ;
    in_port_t port = atoi(servPort);
    sockaddr_in servaddr;

    servaddr.sin_addr.s_addr = /*atoi(servIP)*/INADDR_ANY;//tells the os to take care of the ip address
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = port;

    if ((conn_s = socket (AF_INET, SOCK_STREAM, 0)) < 0) {
        printf(" Socket error\n");
    }
    if (connect (conn_s, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
        printf("Connection Error\n");
    }

    /*Writeline( conn_s, buffer, strlen(buffer));
    Readline(conn_s, buffer, MAX_LINE-1);*/
    close(conn_s);
}

ssize_t Readline(int sockd, void *vptr, size_t maxlen) {
    for (int n = 1; n < maxlen; n++ ) {
        char c;
        int rc;
        if ( (rc = read(sockd, &c, 1)) == 1 ) {
            //choose(&c, FILE* infile);
        }
        else if ( rc == 0 ) {

        }
        else {
            if (errno == EINTR)
                continue;
            return -1;
        }
    }
}

ssize_t Writeline(int sockd, void *vptr, size_t maxlen) {
    int nleft;
    while (nleft > 0) {
        int nwritten;
        if ((nwritten = write(sockd, vptr, nleft)) <= 0 ) {
            if (errno == EINTR)
                nwritten = 0;
            else
                return -1;
        }
    }
}