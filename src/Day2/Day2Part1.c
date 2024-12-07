#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

/* Define constants */
#define MAX_ROWS 2000
#define MAX_LEN 1000
#define MAX_COLUMNS 20

int main() {
    /* Define variables */
    char line[MAX_LEN];
    int Values[MAX_ROWS][MAX_COLUMNS] = {0};
    int rows = 0;
    int cols_per_row[MAX_ROWS] = {0};
    int Row;
    int Column;
    bool Safe;
    bool Increasing;
    bool Decreasing;
    int SafeCount = 0;
    int Diff;
    int AbsDiff;
    int cols; 

    /* Read file */
    FILE * fPointer;
    fPointer = fopen("src/Day2/input.txt", "r");

    /* If there exist no file, return an error */
    if (fPointer == NULL)
    {
        perror("opening input.txt failed");
        return 1;
    }

    /* Reach each line and store values into an array.
     Store also the number of columns at each row. */
    while (fgets(line, sizeof(line), fPointer) != NULL) 
    {
        char *token = strtok(line, " "); 
        cols = 0;

        while (token != NULL && cols < MAX_COLUMNS) {
            Values[rows][cols] = atoi(token); 
            cols++;
            token = strtok(NULL, " ");       
        }
        cols_per_row[rows] = cols - 1;
        rows++;
    }

    /* Loop through each row */
    for (Row = 0; Row < rows; Row++)
    {
        /* Initilize */
        Safe = true;
        Increasing = true;  
        Decreasing = true;

        /* Loop through each column */
        for (Column = 0; Column < cols_per_row[Row]; Column++)
        {
            /* Calculate difference and abs(difference) */
            Diff = Values[Row][Column + 1] - Values[Row][Column];
            AbsDiff = abs(Diff);
            
            /* Check if the difference is too large between two columns */
            if (AbsDiff < 1 || AbsDiff > 3)
            {
                Safe = false;
                break;
            }

            /* Check if the values at the row increase or decrease */
            if (Diff > 0) 
            {
                Decreasing = false;
            }
            else if (Diff < 0)
            {
                Increasing = false;
            } 
        }

        /* Only allow that the row increase OR decrease */
        if (!(Increasing || Decreasing)) 
        {
            Safe = false;
        }

        /* Calculate number of valid/safe rows */
        if (Safe) 
        {
            SafeCount++;
        }
    }
    /*Close the file*/
    fclose(fPointer);

    /* Print the result */
    printf("Number of safe rows are : %d\n", SafeCount);
    return 0;
}