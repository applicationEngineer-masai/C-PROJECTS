#include <stdio.h>

int main(int argc, char const *argv[])
{
    
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int n = sizeof(arr) / sizeof(arr[0])-1;
    int left=0, right=n;

    while(left < right) {
        int temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;
        left++;
        right--;
    }

    for(int i=0; i<=n; i++) {
        printf("%d, ", arr[i]);
    }
    printf("\n");
    return 0;
}
