#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

/* Define constant */
#define DATA_SIZE 100000

/* Get the number */
int FindNumber(int index, char* data, int* newIndex) {
    int number = 0;

    /* Singular */
    if (isdigit(data[index])) 
    {
        number = data[index] - '0';
        *newIndex = index + 1; 
    }

    /* Tens */
    if (isdigit(data[index]) && isdigit(data[index + 1])) 
    {
        number = 10 * (data[index] - '0') + (data[index + 1] - '0');
        *newIndex = index + 2; 
    } 

    /* Hundreds */
    if (isdigit(data[index]) && isdigit(data[index + 1]) && isdigit(data[index + 2])) 
    {
        number = 100 * (data[index] - '0') + 10 * (data[index + 1] - '0') + (data[index + 2] - '0');
        *newIndex = index + 3; 
    }

    /* Return number */
    return number;
}

int main() {
    /* Define variables */
    char character;
    char data[DATA_SIZE];
    int i = 0;
    int index;
    int sum = 0;

    /* Read file */
    FILE * fPointer;
    fPointer = fopen("src/Day3/input.txt", "r");

    /* If there exist no file, return an error */
    if (fPointer == NULL)
    {
        perror("opening input.txt failed");
        return 1;
    }

    /* Store each character in: data */
    while ((character = getc(fPointer)) != EOF) {
        if (character != '\n' && character != ' ') {
            data[i] = character;
            i++;
        }
    }

    /* Loop through data */
    for (index = 0; index < i; index++)
    {
        /* Initilize the numbers */
        int number1 = 0;
        int number2 = 0;

        /* Check 1. Check if the line starts with "mul"*/
        if (data[index] == 'm' && data[index + 1] == 'u' && data[index + 2] == 'l' &&
            data[index + 3] == '(')
        {
            /* Get first number */
            index = index + 4;
            int newIndex;
            number1 = FindNumber(index, data, &newIndex);
            index = newIndex;

            /* Check 2. Check if there is a ',' as seperator between the numbers */
            if (data[index] == ',')
            {
                index++;
                /* Get second number*/
                number2 = FindNumber(index, data, &newIndex);
                index = newIndex;
            }
            else
            {
                continue;
            }

            /* Check 3. Check if there is a valid end*/
            if (data[index] == ')')
            {
                sum += number1 * number2;
            }
        }
    }

    fclose(fPointer);

    /* Print the result */
    printf("The total sum is: %d\n", sum);
    
    return 0;
}