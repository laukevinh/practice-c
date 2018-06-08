/* append items to end of array */
#include <stdio.h>
#include <stdlib.h>
#define SIZE(x) (int) sizeof(x) / (int) sizeof(x[0])

void append(int** intArray, int * length, int i);
void getLineInt(int** intArray_ref, int * length);
void printarray(int* intArray, int length);

int main(void)
{
    // setup
    int length = 1;
    int * intArray = malloc(sizeof(int));

    // get input from user and append ints
    getLineInt(&intArray, &length);

    // append
    for (int j=0; j<5; j++)
        append(&intArray, &length, 11);
    
    // print
    printarray(intArray, length);

    // teardown
    free(intArray);     // DOES THIS FREE THE ENTIRE MALLOC?
    return 0;
}

/* Uses reference to head of an array (pointer to pointer) and 
   reference to array length (pointer) to insert new node at end. */
void append(int** intArray_ref, int * length, int i)
{
    *intArray_ref = realloc(*intArray_ref, sizeof(int) * (++*length));
    *( *intArray_ref + *length - 1 ) = i;
}

/* convenience function to get ints from user parsed by spaces */
void getLineInt(int** intArray_ref, int * length)
{
    char c;
    int i = 0;
    while ((c=getchar())!= '\n' ) {
        if (c == ' ') {
            append(intArray_ref, length, i);
            i = 0;
        } else if (47 < c && c < 58){
            i = (i * 10) + (c - '0');
        }
    }
}


void printarray(int* intArray, int length)
{
    for (int j=0; j<length; j++)
        printf("%i ", *(intArray+j)); 
    printf("\n");
}

