#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>


int main(){

    int fd = open("hello.txt", O_RDONLY);
    //방어로직이 들어가야함
    if(fd == -1){
        perror("open 실패");
        return 1;
    }
    printf("fd : %d\n", fd);

    
    FILE* fp = fopen("hello.txt", "r");
    if(fp == NULL){
        perror("foepn 실패");
        close(fd);
        return 1;
    }
    printf("fd_from_fopen : %d\n", fileno(fp));
    
    fclose(fp);
    close(fd);
    return 0;
}