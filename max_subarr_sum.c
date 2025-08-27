
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int array[] = {2, 1, 4, 3, 6, 5, 7, 6, 8, 7, 9, 0};
    int max_sum = 0;
    int sum = 0;
    int n=sizeof(array)/sizeof(array[0]);
    int k=4;

    // first window initialize
    for(int i=0; i<k; i++) {
        sum += array[i];
        max_sum=sum;
    }

    // using sliding window
    for(int i=k; i<n; i++) {
        sum += array[i] - array[i-k];
        if(sum > max_sum) {
            max_sum = sum;
        }
    }

    printf("MAX SUM %d\n", max_sum);

    return 0;
}
