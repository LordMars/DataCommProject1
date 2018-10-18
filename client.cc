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

    FILE * infile;
    infile = fopen(fpath, "rb");

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

    fseek( infile, 0L , SEEK_END);
    int lSize = ftell( infile );
    rewind( infile );

    char* buffer = (char*)malloc(lSize+1);
    int result;
    while((result = fread(buffer, 1, lSize, infile)) == 1){}

    for(int i = 0; i < lSize; i++){
        printf("%c", buffer[i]);
    }
    int format_int = atoi(format);
    Writeline(conn_s, toname, strlen(toname));//First, send the name of the file to be created
    //Writeline(conn_s, format, strlen(format));//Then, send the format
    write(conn_s, &format_int, 1);
    Writeline( conn_s, buffer, lSize);//Last, send the actual data

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
    printf("\n%s", (char*)vptr);
    while(pread(sockd, vptr, 1, 0) > 0){}//does not finish function unless pipe is empty
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

