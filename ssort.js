
function ssort(arr, n) {
    for (let i=0; i<n-1; i++) {
        let min_idx=i;

        for(let j=i+1; j<n; j++) {
            if(arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        // Swap
        let temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
    return arr;
}


function main() {
    let arr = [5, 3, 7, 2, 9, 1, 0, 6, 3, 5];
    let recv = ssort(arr, arr.length);

    console.log(recv);
}



main();