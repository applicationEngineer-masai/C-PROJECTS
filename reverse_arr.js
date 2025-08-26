
let arr = [1, 2, 3, 4, 5, 6, 7, 8, 9, 0];
let reversedArr = new Array(arr.length);

for (let i = 0; i < arr.length; i++) {
    reversedArr[i] = arr[arr.length - 1 - i];
}

console.log(reversedArr);