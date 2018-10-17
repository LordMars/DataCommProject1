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
void read_0(char* c, FILE* infile);
void read_1(char* c, FILE* infile);
void choose(char* c, FILE* infile);

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
    }else{
        printf("%i \n", servaddr.sin_port);
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
    char c[maxlen];
    vptr = c;
    for (int n = 0; n < maxlen; n++ ) {
        if ( (rc = read(sockd, &c, maxlen)) == 1 ) {
            //if(c[rc - 1] ==){}
        }
        else if ( rc == 0 ) {
            printf("%s\n", (char*)vptr);
            memset(vptr, 0, maxlen);
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

void choose(char* c, FILE* infile){
    if(*c == 0){
        printf("Type: %i ", *c);
        read_0(c, infile);
    }
    else if(*c == 1){
        printf("Type: %i ", *c);
        read_1(c, infile);
    }
}

void read_0(char* c, FILE* infile){
    fread(c, 1, 1, infile);
    int num = int(*c);
    printf("Amount: %i\n", num);

    int i = 0;
    char a;
    char b;

    while(i < num){
        fread(&a, 1, 1, infile);
        fread(&b, 1, 1, infile);
        printf("%i \n", (u_int16_t)((a<<8) + b));//prints the bytes next to one another
        i++;
    }
}

void read_1(char* c, FILE* infile){
    char num[4];
    char cur[6];

    fread(&num[0], 1, 1, infile);
    fread(&num[1], 1, 1, infile);
    fread(&num[2], 1, 1, infile);

    int amount = (num[0]-48)*100 + (num[1]-48)*10 + (num[2]-48);
    printf("Amount: %i \n", amount);
    for(int i = 0; i < amount; i++){
        int j = 0;
        while(fread(c, 1, 1, infile) == 1 && j < 6){ 
            if(*c != ',' && *c != 0 && *c != 1){
                cur[j] = *c;
                j++;
            } 
            else if(*c == ','){
                printf("%s \n", cur);
                memset(cur, 0, 6);
                break;
            }
            else{
                break;
            }  
        }
        if( i == amount-1){
            printf("%s \n", cur);
            choose(c, infile);
        }
    }
}