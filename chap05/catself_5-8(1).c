#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<string.h>

static void do_cat(const char* s);
static void die(const char* s);

int main(int argc, char* argv[]){
    char p[] = "write file path : ";
    char path[1024];
    int n;
    if(argc < 2){
        if(write(STDOUT_FILENO, p, sizeof(p))<0) die("");
        n = read(STDIN_FILENO, path, sizeof(path));
        path[strcspn(path, "\n")] = '\0';
        if(n<0) die("");
        
        do_cat(path);
    }
    
    int i;
    for(i=1; i<argc; i++){
        do_cat(argv[i]);
    }

    exit(0);

}

#define BUFFER_SIZE 2048
static void do_cat(const char* s){
    int fd;
    int n;
    unsigned char buf[BUFFER_SIZE];
    fd = open(s, O_RDONLY);

    if(fd < 0) die(s);

    for(;;){
        n = read(fd, buf, sizeof(buf));
        if(n<0) die(s);
        if(n==0) break;
        if(write(STDOUT_FILENO, buf, n)<0) die(s);
    }
    if(close(fd)<0) die(s);
}

static void die(const char* s){
    perror(s);
    exit(1);
}