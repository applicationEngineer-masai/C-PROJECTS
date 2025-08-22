#include <stdio.h>

int main(int argc, char const *argv[])
{
    
    int arr[] = {1, 1, 1, 2, 3, 3, 4, 5, 6, 7, 8, 8, 8, 8, 8, 8, 9,9,10};
    int i=0;

    for(int j=0; j<sizeof(arr)/sizeof(arr[0]); j++) 
    {    
        if(arr[i] != arr[j]) {
            i++;
            arr[i] = arr[j];
        }
    }

    for(int k=0; k<i+1; k++) {
        printf("%d\t", arr[k]);
    }
    return 0;
}
 