/* size or number of elements in array must use
   static declaration. Passing a pointer explicitly
   or via a parameter will not work because C does
   not know where the rest of the array is located. */
#include <stdio.h>
#include <stdlib.h>
#define SIZE(x) (int) sizeof(x) / (int) sizeof(x[0])

int main(void)
{
    int i = 0;
    printf("size? ");
    scanf("%d", &i);
    int array[i];

    printf("Size=%3d\n", SIZE(array));

    return 0;
}

