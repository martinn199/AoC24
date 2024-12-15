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

    /* Loop through each row. Take boundary conditions into account */
    for (irow = 0; irow < rows - 2; irow++)
    {
        /* Loop through each column. Take boundary conditions into account */
        for (icolumn = 0; icolumn < columns - 2; icolumn++)
        {
            /* There exist 4 combinations that can form the X of MAS, where each
            MAS can be written forward and backward. They are:
            1) M.S    2) S.S    3) M.M    4) S.M 
               .A.       .A.       .A.       .A.
               M.S       M.M       S.S       S.M 
            We need to check all these conditions. But first,do not continue if 
            the "start" and "end" points are correct */
            if (!((data[irow][icolumn] == 'M' && data[irow][icolumn + 2] == 'S') ||
                (data[irow][icolumn] == 'S' && data[irow][icolumn + 2] == 'S') ||
                (data[irow][icolumn] == 'M' && data[irow][icolumn + 2] == 'M') ||
                (data[irow][icolumn] == 'S' && data[irow][icolumn + 2] == 'M')))
            {
                continue;
            }
            /* Test all combinations */
            /* ====== Combination 1) ====== */
            bool combination1LeftDiag = data[irow][icolumn] == 'M' && 
                                        data[irow + 1][icolumn + 1] == 'A' && 
                                        data[irow + 2][icolumn + 2] == 'S';
            bool combination1RightDiag = data[irow][icolumn + 2] == 'S' && 
                                        data[irow + 1][icolumn + 1] == 'A' && 
                                        data[irow + 2][icolumn] == 'M';
            bool combination1 = combination1LeftDiag && combination1RightDiag;

            /* ====== Combination 2) ====== */
            bool combination2LeftDiag = data[irow][icolumn] == 'S' && 
                                        data[irow + 1][icolumn + 1] == 'A' && 
                                        data[irow + 2][icolumn + 2] == 'M';
            bool combination2RightDiag = data[irow][icolumn + 2] == 'S' && 
                                        data[irow + 1][icolumn + 1] == 'A' && 
                                        data[irow + 2][icolumn] == 'M';
            bool combination2 = combination2LeftDiag && combination2RightDiag;

            /* ====== Combination 3) ====== */
            bool combination3LeftDiag = data[irow][icolumn] == 'M' && 
                                        data[irow + 1][icolumn + 1] == 'A' && 
                                        data[irow + 2][icolumn + 2] == 'S';
            bool combination3RightDiag = data[irow][icolumn + 2] == 'M' && 
                                        data[irow + 1][icolumn + 1] == 'A' && 
                                        data[irow + 2][icolumn] == 'S';
            bool combination3 = combination3LeftDiag && combination3RightDiag;

            /* ====== Combination 4) ====== */
            bool combination4LeftDiag = data[irow][icolumn] == 'S' && 
                                        data[irow + 1][icolumn + 1] == 'A' && 
                                        data[irow + 2][icolumn + 2] == 'M';
            bool combination4RightDiag = data[irow][icolumn + 2] == 'M' && 
                                        data[irow + 1][icolumn + 1] == 'A' && 
                                        data[irow + 2][icolumn] == 'S';
            bool combination4 = combination4LeftDiag && combination4RightDiag;

            /* If one of the combinations is true, increase the counter */
            if (combination1 || combination2 || combination3 || combination4)
            {
                count++;
            }
        }
    }

    /* Print the result */
    printf("The number of times X-MAS appear are: %d\n", count);
    return 0;
}