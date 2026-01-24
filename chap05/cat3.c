#include<stdio.h>
#include<stdlib.h>

void cat(FILE* f);

int main(int argc, char* argv[]){

    if(argc < 2) {
        cat(stdin);
    }
    int i;

    for(i=1; i<argc; i++){
        FILE* fd = fopen(argv[i], "r");
        if(!fd) {
            perror(argv[i]);
            exit(1);
        }
        cat(fd);

        fclose(fd);
    }

    exit(0);

}

#define BUFFER_SIZE 2048
#define FILE_SIZE 1024

void cat(FILE* s){
    
    char c;

    while((c=fgetc(s)) != EOF){
        if(putchar(c) < 0) exit(1);
    }

}