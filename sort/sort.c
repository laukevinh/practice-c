/*  Sorting routines
    
    merge, quick, insertion, selection, heap?, bubble?
*/

/*  Merge sort

    Recursively divide array in half until array size 
    is one, then merge and return both halves up the stack.
    Array is divided in half log n times (depth).
    Each time it merges, there is Theta(n) work, thus
    total time complexity is Theta(n log n).

    n auxillary space is used during the merge routine.
    Since merge routine occurs after the recursive calls,
    space complexity is Theta(n).
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
    
    Select one element p from the array. Rearrange
    the array so elements to the left are < p and
    elements to the right are > p. Quick sort the
    remaining left and right parts without p.

    Time complexity is O(n^2), such as when all 
    elements are the same value. Each iteration
    returns the array with just 1 less element to 
    look at. Total work is n + (n-1) + (n-2) ... 1.

    Improve expected running time by looking at 3
    elements and set p to the median before sorting. 
    This can be done by looking at values at positions
    0, n/2, and n-1, then swap values so arr[n-1] is
    the median. If array is arranged high to low, this 
    preprocessing step reduces the number of compares.
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
            swap(arr, ++i, j);
        }
    swap(arr, ++i, high-1);
    return i;
}
 
void preprocess(int arr[], int low, int high)
{
    high--;
    int mid = low + (high-low)/2;
    if (arr[high] > arr[low])
        swap(arr, low, high);
    if (arr[high] < arr[mid])
        swap(arr, mid, high);
    if (arr[high] > arr[low])
        swap(arr, low, high);
}

void quick_sort(int arr[], int low, int high)
{
    if (low < high) {
        preprocess(arr, low, high);
        int p = partition(arr, low, high);
        quick_sort(arr, low, p);
        quick_sort(arr, p+1, high);
    }
}

/*  Insertion sort
    
    For i = 1, 2, ... n
    Insert A[i] into sorted array A[0:i-1]
    by pairwise swaps down to the correct position.
    Similar to how you would sort a hand of cards.

    Time complexity is O(n^2), such as when
    array is sorted in reverse order. For arrays
    that are almost sorted, time complexity is
    minimized. Binary insertion sort can reduce the
    number of compares by using binary search,
    but the overall time required is still n^2 due
    to the swaps.
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

/*  selection sort
    
    Starting with i=0, find the smallest item 
    from i to n, and swap with i. Repeat with
    i+1, i+2, until complete.

    Time complexity is Theta(n^2). Each iteration
    only produces an array length 1 less than 
    the previous, so n + (n-1) + (n-2) ... 1.

    This is an in place sorting algorithm. It only
    requires at most O(n) swaps, making it a
    efficient when memory swaps are expensive.
*/

void selection_sort(int arr[], int len)
{
    for (int i=0; i<len; i++) {
        int min = i;
        for (int j=i; j<len; j++)
            if (arr[j] < arr[min])
                min = j;
        swap(arr, i, min);
    }
}

/*  bubble sort

    Traverse array, swaping adjacent elements if not
    in order. Repeat until there are no swaps in
    one traversal.

    Time complexity is O(n^2) since each iteration
    traverses the entire array just to push the max 
    element in each iteration to the top. There may be
    as many iterations as there are elements, such as
    a completely reversed array.
*/

void bubble_sort(int arr[], int len)
{
    int swap_ct = 1;
    while (swap_ct > 0) {
        swap_ct = 0;
        for (int i=1; i<len; i++) {
            if (arr[i] < arr[i-1]) {
                swap(arr, i, i-1);
                swap_ct++;
            }
        }
    }
}



