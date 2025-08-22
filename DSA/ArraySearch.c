#include <stdio.h>

#define MAX 5

int main(int argc, char const *argv[])
{
    int arr[] = {1, 3, 2, 5, 7, 6, 8, 7, 0};
    int item=7;

    int Found[MAX];
    int position[MAX];
    int index[MAX];

    int count=0;

    for(int i=0; i<sizeof(arr)/sizeof(arr[0]); i++) {
        if(arr[i] == item) {
            Found[count]=item;
            position[count]=i+1;
            index[count]=i;
            count++;
        }
    }

    printf("=======================FOUND STATUS=============================\n");
    for(int i=0; i<count; i++) {
        printf("\n");
        printf("||\t\tItem Name : %d\n", Found[i]);
        printf("||\t\tItem Position : %d\n", position[i]);
        printf("||\t\tItem Index : %d\n\n", index[i]);
    }
    printf("================================================================\n");
    return 0;
}
