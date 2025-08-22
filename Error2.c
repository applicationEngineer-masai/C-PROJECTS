#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(int argc, char const *argv[])
{
    FILE *FD;

    FD = fopen("file_not_exist.txt", "r");
    if(FD == NULL) {
        printf("Error says %s\n", strerror(errno));
    }
    return 0;
}
