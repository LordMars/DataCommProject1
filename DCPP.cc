#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_0(char* c, FILE* infile);
void read_1(char* c, FILE* infile);
void choose(char* c, FILE* infile);

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
        choose(&c, infile);
    }
    return 0;
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