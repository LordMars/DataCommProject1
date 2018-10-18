#include <sys/socket.h> /* socket definitions */
#include <sys/types.h> /* socket types */
#include <arpa/inet.h> /* inet (3) funtions */
#include <unistd.h> /* misc. UNIX functions */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define ECHO_PORT (2002)
#define MAX_LINE (1000)

ssize_t Readline(int sockd, void *vptr, size_t maxlen, char* infile, char* outfile);
ssize_t Writeline(int sockd, void *vptr, size_t maxlen);
void read_0(char* c, int sockd);
void read_1(char* c, int sockd);
void choose(char* c, int sockd);

int main(int argc, char *argv[]){
    if (argc != 2){
        printf("Wrong number of arguments.");
        exit(1);
    }

    int list_s;
    int LISTENQ = 0;
    int conn_s;

    in_port_t port = atoi(argv[1]);

    sockaddr_in servaddr;

    servaddr.sin_addr.s_addr = INADDR_ANY;//tells the os to take care of the ip address
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = port;


    if ((list_s = socket (AF_INET, SOCK_STREAM, 0)) < 0) {//creates a socket
        printf("Socket Error. \n");
    }
    if (bind (list_s, (struct sockaddr *) &servaddr, sizeof(servaddr))< 0) {//binds the socket to a given port and ipaddress
        printf("Binding Error. \n");
    }
    if (listen (list_s, LISTENQ) < 0) {//waits for a client application to connect to the server
        printf("Listening Error. \n");
    }
    while ( 1 ) {
        sockaddr cliaddr[MAX_LINE];
        socklen_t addrlen[MAX_LINE];
        char buffer[MAX_LINE];
        char infile_name[MAX_LINE];
        char outfile_name[MAX_LINE];

        if ((conn_s = accept (list_s, cliaddr, addrlen)) < 0) {//accepts an incoming connection from a client socket
            printf("%i\n",list_s);
            printf("%i\n",*addrlen);
            printf("Accepting Error\n");
        }
        Readline (conn_s, buffer, MAX_LINE-1, infile_name, outfile_name);
        //Writeline( conn_s, buffer, strlen(buffer));
        if ( close (conn_s) < 0 ) {
            
        }
    }  

}

ssize_t Readline(int sockd, void *vptr, size_t maxlen, char* infile, char* outfile) {
    int rc;
    char c;
    for (int n = 0; n < maxlen; n++ ) {
        if ( (rc = read(sockd, &c, 1)) == 1 ) {
            choose(&c, sockd);
        }
        else if ( rc == 0 ) {
            /*printf("%s\n", (char*)vptr);
            memset(vptr, 0, maxlen);*/
            break;
        }
        else {
            if (errno == EINTR)
                continue;
            memset(vptr, 0, maxlen);
            return -1;
        }
    }
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

void choose(char* c, int sockd){
    if(*c == 0){
        read_0(c, sockd);
    }
    else if(*c == 1){
        read_1(c, sockd);
    }
}

void read_0(char* c, int sockd){
    int rc;
    int num;
    if ( (rc = read(sockd, c, 1)) == 1 ) {
        num = int(*c);
        printf("Amount: %i\n", num);
    }
    else if ( rc == 0 ) {}

    int i = 0;
    char a;
    char b;

    while(i < num){
        if ( (rc = read(sockd, &a, 1)) == 1 ) {}
        else if ( rc == 0 ) {}

        if ( (rc = read(sockd, &b, 1)) == 1 ) {}
        else if ( rc == 0 ) {}

        printf("%i \n", (u_int16_t)((a<<8) + b));//prints the bytes next to one another
        i++;
    }
}

void read_1(char* c, int sockd){
    char num[4];
    char cur[6];

    /*fread(&num[0], 1, 1, infile);
    fread(&num[1], 1, 1, infile);
    fread(&num[2], 1, 1, infile);*/
    int rc;
    if ( (rc = read(sockd, &num, 3)) == 3 ) {}
    else {}//error

    int amount = (num[0]-48)*100 + (num[1]-48)*10 + (num[2]-48);
    printf("Amount: %i \n", amount);
    memset(cur, 0, 6);
    for(int i = 0; i < amount; i++){
        int j = 0;
        int rc;
        while((rc = read(sockd, c, 1)) == 1/*fread(c, 1, 1, infile) == 1*/ && j < 6){ 
            if(*c != ',' && *c != 0 && *c != 1){
                cur[j] = *c;
                j++;
            } 
            else if(*c == ','){
                printf("%s\n", cur);
                memset(cur, 0, 6);
                break;
            }
            else{
                break;
            }  
        }
        if( i == amount-1){
            printf("%s \n", cur);
            choose(c, sockd);
        }
    }
}