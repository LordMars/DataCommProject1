#include <stdio.h>
#include <stdlib.h>

void read_0(char* c, FILE* infile);
void read_1(char* c, FILE* infile);

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
        if(c == 0){
            printf("%i \n", c);
            read_0(&c, infile);
        }
        else if(c == 1){
            printf("%i \n", c);
            read_1(&c, infile);
        }
        //printf("%c \n", c);
    }
    return 0;
}

void read_0(char* c, FILE* infile){
    fread(c, 1, 1, infile);
    int num = int(*c);
    printf("%i %i \n", *c, num);

    int i = 0;
    char a;
    char b;

    while(i < 2){
        fread(&a, 1, 1, infile);
        fread(&b, 1, 1, infile);
        printf("%c%c ", a, b);
        i++;
    }
    printf("\n");
};

void read_1(char* c, FILE* infile){
    char one, two, three;
    fread(&one, 1, 1, infile);
    fread(&two, 1, 1, infile);
    fread(&three, 1, 1, infile);
    
    while(fread(c, 1, 1, infile) == 1){
        if(*c != 0 || *c != 1){
            printf("%c", *c);
        } else{
            printf("%i \n", *c);
            break;
        }
    }
};