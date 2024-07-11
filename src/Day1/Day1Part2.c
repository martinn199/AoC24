#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*Define constants*/
#define MAX_ROWS 1000
#define MAX_LEN 100

int main() {
    /*Define variables*/
    char line[MAX_LEN];
    int i, length;
    int j = 0;
    int FoundFirstDigit = 0;

    /*Store calibration values and the sum of all of the calibration values*/
    char CalVal[MAX_ROWS][2] = {0};
    int TotCalVal = 0;

    /*Read file*/
    FILE * fPointer;
    fPointer = fopen("src/Day1/input.txt", "r");

    /*If there exist no file, return an error*/
    if (fPointer == NULL)
    {
        perror("opening input2.txt failed");
        return 1;
    }

    /*Loop though each line of text*/
    while(fgets(line, sizeof(line), fPointer) != NULL){
        FoundFirstDigit = 0;
        length = strlen(line);

        /*Transform the letters to digits*/
        for(i = 0; i < length; i++){
            if(line[i] == 'o' && line[i+1] == 'n' && line[i+2] == 'e'){
                line[i] = '1';
            }
            else if(line[i] == 't' && line[i+1] == 'w' && line[i+2] == 'o'){
                line[i] = '2';
            }
            else if(line[i] == 't' && line[i+1] == 'h' && line[i+2] == 'r' && line[i+3] == 'e' && line[i+4] == 'e'){
                line[i] = '3';
            }
            else if(line[i] == 'f' && line[i+1] == 'o' && line[i+2] == 'u' && line[i+3] == 'r'){
                line[i] = '4';
            }
            else if(line[i] == 'f' && line[i+1] == 'i' && line[i+2] == 'v' && line[i+3] == 'e'){
                line[i] = '5';
            }
            else if(line[i] == 's' && line[i+1] == 'i' && line[i+2] == 'x'){
                line[i] = '6';
            }
            else if(line[i] == 's' && line[i+1] == 'e' && line[i+2] == 'v' && line[i+3] == 'e' && line[i+4] == 'n'){
                line[i] = '7';
            }
            else if(line[i] == 'e' && line[i+1] == 'i' && line[i+2] == 'g' && line[i+3] == 'h' && line[i+4] == 't'){
                line[i] = '8';
            }
            else if(line[i] == 'n' && line[i+1] == 'i' && line[i+2] == 'n' && line[i+3] == 'e'){
                line[i] = '9';
            }

            /*Store the first and last digit to form the calibration value*/
            if(isdigit(line[i]) && !FoundFirstDigit){
                FoundFirstDigit = 1;
                CalVal[j][0] = line[i];
            }
            else if(isdigit(line[i]) && FoundFirstDigit){
                CalVal[j][1] = line[i];
            }
        }

        /*If there only exists one digit, dublicate it*/
        if(!isdigit(CalVal[j][1])){
            CalVal[j][1] = CalVal[j][0];
        }

        /*Calculate the sum of calibration values*/
        TotCalVal += atoi(CalVal[j]);

        j++;
    }

    /*Close the file*/
    fclose(fPointer);

    /*Print the results*/
    printf("Sum of all of Calibration Values are: %d\n", TotCalVal);
    return 0;
}