/* push new elemnt to front */
#include <stdio.h>
#include <stdlib.h>
#define SIZE(x) (int) sizeof(x) / (int) sizeof(x[0])

int main(void)
{
    int length = 0;
    printf("size? ");
    scanf("%d", &length);

    int * intArray = malloc(sizeof(int) * length);

    for (int j=0; j<length; j++)
        *(intArray+j) = j;

    for (int j=0; j<length; j++)
        printf("%p %i \n", intArray+j, *(intArray+j)); 

    free(intArray);     // DOES THIS FREE THE ENTIRE MALLOC?
    return 0;
}

