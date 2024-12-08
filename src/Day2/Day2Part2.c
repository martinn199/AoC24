#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

/* Define constants */
#define MAX_ROWS 2000
#define MAX_LEN 1000
#define MAX_COLUMNS 20

/* First do a regular check as in part 1 and return if the report is safe or not */
bool CheckSafeReport(int Values[], int Columns) 
{
    /* Initilize */
    bool SafeReport = true;
    bool Increasing = true;  
    bool Decreasing = true;
    int Diff, AbsDiff, Column;

    /* Loop through the columns */
    for (Column = 0; Column < Columns; Column++)
    {
        /* Calculate difference and abs(difference) */
        Diff = Values[Column + 1] - Values[Column];
        AbsDiff = abs(Diff);

        /* Check if the difference is too large between two columns */
        if (AbsDiff < 1 || AbsDiff > 3)
        {
            SafeReport = false;
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
        SafeReport = false;
    }

    /* Return if the report is safe or not */
    return SafeReport;
}

/* Check if a report can be made safe by removing one level */
bool CheckUnsafeReport(int Values[], int cols) 
{
    int i, j;

    /* Remove one columns at the time */
    for (i = 0; i <= cols; i++) 
    {
        /* After removed the column, create a new report (where the column has been deleted) */
        int NewValues[MAX_COLUMNS] = {0};
        int NewCols = 0;
        for (j = 0; j <= cols; j++) 
        {
            if (j != i) 
            {
                NewValues[NewCols++] = Values[j];
            }
        }

        /* Check if the new report is safe */
        if (CheckSafeReport(NewValues, NewCols - 1)) 
        {
            return true;
        }
    }

    return false;
}

int main() {
    /* Define variables */
    char line[MAX_LEN];
    int Values[MAX_ROWS][MAX_COLUMNS] = {0};
    int Rows = 0;
    int ColumnsPerRow[MAX_ROWS] = {0};
    int Row;
    int SafeCount = 0;
    int Columns; 
    bool SafeReport;

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
        Columns = 0;

        while (token != NULL && Columns < MAX_COLUMNS) {
            Values[Rows][Columns] = atoi(token); 
            Columns++;
            token = strtok(NULL, " ");       
        }
        ColumnsPerRow[Rows] = Columns - 1;
        Rows++;
    }

    /* Loop through each report/row */
    for (Row = 0; Row < Rows; Row++)
    {
        /* First do a regular check as in part 1 and return if the report is safe or not */
        SafeReport = CheckSafeReport(Values[Row], ColumnsPerRow[Row]);

        /* If a report is not safe, check if the report can be safe if a single level from
         an unsafe is removed */
        if (!SafeReport)
        {
            SafeReport = CheckUnsafeReport(Values[Row], ColumnsPerRow[Row]);
        }

        /* Calculate number of safe reports */
        if (SafeReport) 
        {
            SafeCount++;
        }
    }
    
    /*Close the file*/
    fclose(fPointer);

    /* Print the result */
    printf("Number of safe reports are : %d\n", SafeCount);
    return 0;
}