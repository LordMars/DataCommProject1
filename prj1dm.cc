#include <sys/socket.h> /* socket definitions */
#include <sys/types.h> /* socket types */
#include <arpa/inet.h> /* inet (3) funtions */
#include <unistd.h> /* misc. UNIX functions */

#include <stdlib.h>
#include <stdio.h>
/* Global constants */
#define ECHO_PORT (2002)
#define MAX_LINE (1000)

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

    int list_s;

    if ((list_s = socket (PF_INET, SOCK_STREAM, 0)) < 0) {

    }
    if (bind (list_s, (struct sockaddr *) &servIP, sizeof(servIP)) < 0) {

    }
    /*if (listen (list_s, LISTENQ) < 0) {

    }*/
    /*while ( 1 ) {
        if ((conn_s = accept (list_s, NULL, NULL)) < 0) {

        }
        Readline (conn_s, buffer, MAX_LINE-1);
        Writeline( conn_s, buffer, strlen(buffer));
        if ( close (conn_s) < 0 ) {

        }
    }*/
}