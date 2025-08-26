

let arr = [1, 2, 3, 4, 5, 6, 7, 8, 9, 0];

let reciprocalSum = new Array(arr.length).fill(0);

let left=0;
let right=arr.length-1;
let count = 0;

while(left < right) {
    let sum = arr[left] + arr[right];
    reciprocalSum[left] = sum;
    reciprocalSum[right] = sum;
    left++;
    right--;
}

// print
console.log(reciprocalSum);