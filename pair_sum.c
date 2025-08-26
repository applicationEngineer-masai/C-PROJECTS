#include <stdio.h>

int main(int argc, char const *argv[])
{
    int arr[] = {2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n=sizeof(arr)/sizeof(arr[0]);
    int target = 15;
    int left=0, right = n-1;

    while(left < right) {
        int current_sum = arr[left] + arr[right];
        if(current_sum == target) {
            printf("Pair found: (%d, %d) = %d\n", arr[left], arr[right], current_sum);
            return 0;
        } else if(current_sum < target) {
            left++;
        } else {
            right--;
        }
    }
    printf("No pair found\n");
    return 0;
}
