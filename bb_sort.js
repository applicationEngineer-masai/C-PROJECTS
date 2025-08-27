

function bubble_sort(arr) {

    let n=arr.length;

    for(let i=0; i<n-1; i++) {
        let is_swapped=false;

        for(let j=0; j<n-i-1; j++) {
            if(arr[j] > arr[j+1]) {
                [arr[j], arr[j+1]] = [arr[j+1], arr[j]];
                is_swapped=true;
            }
        }
        if(!is_swapped) {
            break;
        }
    }
    console.log(arr)
}

array = [6, 33, 99, 55, 11, 45, 76, 33];
bubble_sort(array);