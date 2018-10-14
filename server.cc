#include <sys/socket.h> /* socket definitions */
#include <sys/types.h> /* socket types */
#include <arpa/inet.h> /* inet (3) funtions */
#include <unistd.h> /* misc. UNIX functions */

#include <stdlib.h>
#include <stdio.h>

#define ECHO_PORT (2002)
#define MAX_LINE (1000)

int main(int argc, char *argv[]){
    if (argc != 2){
        printf("Wrong number of arguments.");
        exit(1);
    }

    int list_s;
    int LISTENQ = 0;
    in_port_t port = atoi(argv[1]);
    sockaddr_in servaddr;

    servaddr.sin_addr.s_addr = INADDR_ANY;//tells the os to take care of the ip address
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = port;

    if ((list_s = socket (AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket Error. \n");
    }
    if (bind (list_s, (struct sockaddr *) &servaddr, sizeof(servaddr))< 0) {
        printf("Binding Error. \n");
    }
    if (listen (list_s, LISTENQ) < 0) {
        printf("Listening Error. \n");
    }
    /*while ( 1 ) {
        if ((conn_s = accept (list_s, NULL, NULL)) < 0) {}
        Readline (conn_s, buffer, MAX_LINE-1);
        Writeline( conn_s, buffer, strlen(buffer));
        if ( close (conn_s) < 0 ) {}
    }
    */

}