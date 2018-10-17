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

    FILE * infile;
    infile = fopen(argv[1], "rb");

    int conn_s;
    int LISTENQ;
    in_port_t port = atoi(servPort);
    sockaddr_in servaddr;

    memset(&servaddr, 0, sizeof(servaddr));
    if (inet_aton (servIP, &servaddr.sin_addr) <= 0) {
        printf("Invalid IP. \n");
    }
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = port;

    if ((conn_s = socket (AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket error\n");
    }
    if (connect (conn_s, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
        printf("Connection Error\n");
    }

    int length = ftell(infile);
    fread(buffer, 1, length, infile);
    fclose(infile);

    Writeline( conn_s, buffer, strlen(buffer));

    /*buffer = toname;
    strcat(buffer, "\n");
    Writeline( conn_s, buffer, strlen(buffer));*/

    close(conn_s);
}

ssize_t Writeline(int sockd, void *vptr, size_t maxlen) {
    int nleft = maxlen;
    int nwritten;

    while (nleft > 0) {
        if ((nwritten = write(sockd, vptr, nleft)) <= 0 ) {
            if (errno == EINTR)
                nwritten = 0;
            else
                return -1;
        }else{
            nleft-=nwritten;
        }
    }
}

ssize_t Readline(int sockd, void *vptr, size_t maxlen) {
    for (int n = 1; n < maxlen; n++ ) {
        char c;
        int rc;
        if ( (rc = read(sockd, &c, 1)) == 1 ) {
            printf("%i\n", c);
        }
        else if ( rc == 0 ) {
            break;
        }
        else {
            if (errno == EINTR)
                continue;
            return -1;
        }
    }
}

