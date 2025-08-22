#include <stdio.h>
#include <fcntl.h> // ATTRIBUTE
#include <unistd.h> // system call

#define MAX 1024

int main(void) 
{

    char buff[MAX];
    // int fd = open("Test.txt", O_WRONLY | O_CREAT, 0644); // creat and write if needed
    // int fd = open("Test.txt", O_RDWR | O_APPEND);
    int fd = open("Test.txt", O_RDONLY); // read system call

    if(fd < 0) {
        fprintf(stderr, "can not open file");
        return -1;
    }

    ssize_t bytesRead;

    // invoke read system call
    while((bytesRead = read(fd, buff, sizeof(buff))) > 0) {
        buff[bytesRead] = '\0';
        printf("%s\n", buff);
    }

    if(bytesRead < 0) {
        perror("Read error");
    }

    close(fd);
    return 0;
}