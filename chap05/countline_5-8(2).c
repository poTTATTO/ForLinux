#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<string.h>

static void die(const char* string);
static void check_line(const char* path);

int main(int argc, char** argv){
    if(argc < 2){
        fprintf(stderr, "%s : 파일이 하나뿐인교\n", argv[0]);
        exit(1);
    }

    int i;
    for(i=1; i<argc; i++){
        check_line(argv[i]);
    }

    exit(0);
}

#define BUFFER_SIZE 1024

static void check_line(const char* path){
    int fd;
    int n;
    int count=0;
    char buf[BUFFER_SIZE];
    char count_buf[BUFFER_SIZE];

    fd = open(path, O_RDONLY);
    if(fd < 0) die(path);

    for(;;){
        n = read(fd, buf, sizeof(buf));
        if(n<0) die(path);
        if(n==0) break;
        for(int i=0; i<sizeof(buf); i++){
            if(buf[i] == '\n'){
                count++;
            }
        }

    }

    int len = snprintf(count_buf, sizeof(count_buf), "%d", count);

    if(write(STDOUT_FILENO, count_buf, len)< 0) die(path);
    if(write(STDOUT_FILENO, " ", 1)<0) die(path);
    if(write(STDOUT_FILENO, path, strlen(path)));

    if(close(fd) < 0) die(path);

    exit(0);
}

static void die(const char* path){
    perror(path);
    exit(1);
}