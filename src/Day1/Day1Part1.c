#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

/* Define constants */
#define MAX_ROWS 1000
#define MAX_LEN 20

/* Sort the array */
int SortColumn(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    /* Define variables */
    char line[MAX_LEN];
    int ValuesLeft[MAX_ROWS];
    int ValuesRight[MAX_ROWS];
    int LeftValue;
    int RightValue;
    int Sum = 0;
    int i = 0;

    /* Read file */
    FILE * fPointer;
    fPointer = fopen("src/Day1/input.txt", "r");

    /* If there exist no file, return an error */
    if (fPointer == NULL)
    {
        perror("opening input2.txt failed");
        return 1;
    }

    /* Read each line and store left column and right column */
    while (fgets(line, sizeof(line), fPointer) != NULL) 
    {
        sscanf(line, "%d %d", &LeftValue, &RightValue);
        ValuesLeft[i] = LeftValue;
        ValuesRight[i] = RightValue;
        i++;
    }

    /* Close the file */
    fclose(fPointer);

    /* Sort the arrays */
    qsort(ValuesLeft, MAX_ROWS, sizeof(int), SortColumn);
    qsort(ValuesRight, MAX_ROWS, sizeof(int), SortColumn);

    /* Calculate the sum */
    for (i = 0; i < MAX_ROWS; i++) {
        Sum += abs(ValuesLeft[i] - ValuesRight[i]); 
    }

    /* Print the result */
    printf("Similarity score is: %d\n", Sum);
    return 0;
}