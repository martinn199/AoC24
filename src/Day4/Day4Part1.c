#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

/* Define constant */
#define MAX_COLUMNS 200
#define MAX_ROWS 200

int main() {
    /* Define variables */
    char data[MAX_ROWS][MAX_COLUMNS];
    char line[MAX_COLUMNS];
    int rows = 0;
    int columns;
    int irow, icolumn;
    int count = 0;

    /* Read file */
    FILE * fPointer;
    fPointer = fopen("src/Day4/input.txt", "r");

    /* If there exist no file, return an error */
    if (fPointer == NULL)
    {
        perror("opening input.txt failed");
        return 1;
    }

    /* Reach each line and store values into an array */
    while (fgets(line, sizeof(line), fPointer) != NULL) 
    {
        line[strcspn(line, "\n")] = 0;
        strncpy(data[rows], line, MAX_COLUMNS);
        rows++;
    }
    fclose(fPointer);

    /* Calculate number of columns */
    columns = sizeof(data[0]) / sizeof(data[0][0]);

    /* Loop through each row */
    for (irow = 0; irow < rows; irow++)
    {
        /* Loop through each column */
        for (icolumn = 0; icolumn < columns; icolumn++)
        {
            /* Do not continue if the character is not X */
            if (data[irow][icolumn] != 'X')
            {
                continue;
            }

            /* Search in vertical, longitudinal, diagonal.
            Also search backwards and frontwards*/
            int drows[] = {-1, 0, 1};
            int dcolumns[] = {-1, 0, 1};
            int iterations = sizeof(drows) / sizeof(drows[0]);
            int i, j;
            for (i = 0; i < iterations; i++)
            {
                int drow = drows[i];
                for (j = 0; j < iterations; j++)
                {
                    int dcolumn = dcolumns[j];

                    /* If the row and the column are equal. That means that we are looking at
                    the same character. Do not consider that case. */
                    if (dcolumn == 0 && drow == 0)
                    {
                        continue;
                    }
                    /* Boundary conditions, that is we need to be inside the "grid" */
                    if (!((0 <= irow + 3 * drow && irow + 3 * drow < rows) &&
                        (0 <= icolumn + 3 * dcolumn && icolumn + 3 * dcolumn < columns)))
                    {
                        continue;
                    }
                    /* Check if we have found XMAS. If so, increase the counter */
                    if (data[irow + drow][icolumn + dcolumn] == 'M' && 
                        data[irow + 2 * drow][icolumn + 2 * dcolumn] == 'A' && 
                        data[irow + 3 * drow][icolumn + 3 * dcolumn] == 'S')
                    {
                        count++;
                    }
                }
            }
        }
    }

    /* Print the result */
    printf("The number of times XMAS appear are: %d\n", count);
    
    return 0;
}