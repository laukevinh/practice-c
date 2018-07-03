/*  bubble, quick, insertion, selection, merge, heap*/

/*  Insertion sort
    
    For i = 1, 2, ... n
    Insert A[i] into sorted array A[0:i-1]
    by pairwise swaps down to the correct position
    i.e. left < i < right

*/

void insertion_sort(int arr[], int len)
{
    int temp;
    for (int i=1; i<len; i++) {
        for (int j=i; arr[j] < arr[j-1] && j>0; j--) {
            temp = arr[j];
            arr[j] = arr[j-1];
            arr[j-1] = temp;
        }
    }
}

/*  Merge sort

    Recursively divide array in half until array size 
    is one, then merge and return both halves up the stack.
    Array is divided in half log n times (depth).
    Each time it merges, there is Theta(n) work, thus
    total time complexity is Theta(n log n).
*/

void merge(int arr[], int low, int mid, int high)
{
    //  get length for left and right halves
    int left_len = mid - low;
    int right_len = high - mid;

    //  temp arrays
    int L[left_len], R[right_len];

    //  copy data
    for (int i=0; i < left_len; i++)
        L[i] = arr[low + i];
    for (int j=0; j < right_len; j++)
        R[j] = arr[mid + j];

    /*  Merge both halves. Since we're always working
        on the original array, k needs to start at low.
        After one half is complete, copy other half.
    */
    for (int i=0, j=0, k=low; k < high; k++) {
        if (i < left_len && j < right_len) {
            if (L[i] < R[j]) {
                arr[k] = L[i++];
            } else {
                arr[k] = R[j++];
            }
        } else if (i < left_len) {
            arr[k] = L[i++];
        } else {
            arr[k] = R[j++];
        }
    }
}

void merge_sort(int arr[], int low, int high)
{
    //  only arrays with size > 1 need to be sorted
    if (high-low > 1) {
        int mid = low + (high-low) / 2;
        merge_sort(arr, low, mid);
        merge_sort(arr, mid, high);
        merge(arr, low, mid, high);
    }
}

/*  Quick sort
    
    Select one element i from the array. Rearrange
    the array so elements to the left are < i and
    elements to the right are > i. Quick sort the
    remaining left and right partitions.
*/

void swap(int arr[], int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high-1];
    int i = low - 1;
    for (int j=low; j<high-1; j++)
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    int temp = arr[i+1];
    arr[i+1] = arr[high-1];
    arr[high-1] = temp;
    return i+1;
}
            

void quick_sort(int arr[], int low, int high)
{
    if (low < high) {
        int p = partition(arr, low, high);
        quick_sort(arr, low, p);
        quick_sort(arr, p+1, high);
    }
}
/*  selection sort
    
    
*/
