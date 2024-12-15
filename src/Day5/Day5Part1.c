#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

/* Define constant */
#define MAX_NUMBER_PAGES 1176
#define PAGE_NUMBER_XY 2
#define CHARACTER_PER_LINE 500
#define MAX_NUMBER_UPDATES 193
#define MAX_PAGE_PER_UPDATE 193

int main() {
    /* Define variables */
    int pageOrderingRules[MAX_NUMBER_PAGES][PAGE_NUMBER_XY];
    int update[MAX_NUMBER_UPDATES][MAX_PAGE_PER_UPDATE] = {0};
    int pageAtUpdate[MAX_PAGE_PER_UPDATE] = {0};
    char linePageOrder[CHARACTER_PER_LINE];
    int leftNumber, rightNumber, pagePerUpdate, iPageOrder, iUpdate, jUpdate;
    int rows = 0;
    int numberOfUpdates = 0;
    int sum = 0;

    /* Read file */
    FILE * fPointer;
    fPointer = fopen("src/Day5/input.txt", "r");

    /* If there exist no file, return an error */
    if (fPointer == NULL)
    {
        perror("opening input.txt failed");
        return 1;
    }

    /* Reach each page ordering rule and store the left- and right value into an array */
    while (fgets(linePageOrder, sizeof(linePageOrder), fPointer) != NULL
            && linePageOrder[0] != '\n') 
    {
        sscanf(linePageOrder, "%d|%d", &leftNumber, &rightNumber);
        pageOrderingRules[rows][0] = leftNumber;
        pageOrderingRules[rows][1] = rightNumber;
        rows++;
    }

    /* Read the update section and store the page numbers into an array. Also store the number of 
    page number of each update */
    while (fgets(linePageOrder, sizeof(linePageOrder), fPointer) != NULL)
    {
        /* The update section uses a "," as seperator between the page numbers */
        if (linePageOrder[2] != ',')
        {
            continue;
        }

        char *token = strtok(linePageOrder, ","); 
        pagePerUpdate = 0;
        while (token != NULL && pagePerUpdate < MAX_PAGE_PER_UPDATE) 
        {
            update[numberOfUpdates][pagePerUpdate] = atoi(token); 
            pagePerUpdate++;
            token = strtok(NULL, ",");       
        }
        pageAtUpdate[numberOfUpdates] = pagePerUpdate;
        numberOfUpdates++;
    }

    /* Close the file */
    fclose(fPointer);

    /* Loop through each update in the update section */
    for (iUpdate = 0; iUpdate < numberOfUpdates; iUpdate++)
    {
        /* Store if each update is in correct order */
        bool correctOrder = true;

        /* Loop trough each page ordering rule */
        for (iPageOrder = 0; iPageOrder < rows; iPageOrder++)
        {
            /* Get left and right value from the page ordering rule */
            int leftValue = pageOrderingRules[iPageOrder][0];
            int rightValue = pageOrderingRules[iPageOrder][1];

            /* Initializing */
            bool foundLeftValue = false;
            bool foundRightValue = false;
            int indexLeftValue, indexRightValue;

            /* Loop through each page number for the current update section and
            check if left and right value from the page ordering are found there. 
            Also store the index for later use */
            for (jUpdate = 0; jUpdate < pageAtUpdate[iUpdate]; jUpdate++)
            {
                if (leftValue == update[iUpdate][jUpdate])
                {
                    foundLeftValue = true;
                    indexLeftValue = jUpdate;
                }
                else if (rightValue == update[iUpdate][jUpdate])
                {
                    foundRightValue = true;
                    indexRightValue = jUpdate;
                }
            }

            /* If the page numbers for the current update is NOT in correct order set 
            correctOrder = false */
            if (foundLeftValue && foundRightValue && indexLeftValue > indexRightValue)
            {
                correctOrder = false;
                break;
            }
        }

        /* If correctOrder, find the page number of the middle index and add to the sum of them */
        if (correctOrder)
        {
            int halfIndex = pageAtUpdate[iUpdate] / 2;
            sum += update[iUpdate][halfIndex];
        }
    }
    
    /* Print the result*/
    printf("Sum of middle page number from correctly-ordered updates is: %d\n", sum);
    return 0;
}