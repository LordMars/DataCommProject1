#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){

    FILE * infile;
    FILE * outfile;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    if(argc != 3){
        printf("Wrong number of arguments. Give an input and output file.");
        exit(1);
    }

    infile = fopen(argv[1], "rb");
    outfile = fopen(argv[2], "w");

    char c;
    while (fread(&c, 1, 1, infile) == 1){
        printf("%c \n", c);
    }
    return 0;
}

void read_0(){

};

void read_1(){

};