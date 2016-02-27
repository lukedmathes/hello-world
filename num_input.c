/*
************************************************************************************************
num_input.c

This file details a simple input function that can be used to obtain a user inputed number.
************************************************************************************************

The primary function called is get_num_input that takes two arguments. The first is a string
to be printed to stdout indicating to the user what they would like to be inputted, and the
second is a function pointer based off the entry_check type defined below.

get_num_input takes these two arguments and outputs an integer that the user enters when it
meets the appropriate conditions.

If the user does not want to set a condition function, the function no_check can be passed
and any valid number inputted will be returned.



entry_check is a function type that takes one integer and returns a boolean output. A prototype
function has been included below which the programmer can copy and use in their own functions.

*/



#ifndef _NUM_INPUT_C_
#define _NUM_INPUT_C_


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef bool (*entry_check)(int a);

bool no_check(int a);
int get_num_input(char* print_message, entry_check check_condition);


/*
// A Prototype function that can be copied and utilised for any

Inputs: Function takes a single integer that the user has entered.
Outputs: Internally a boolean is outputted from the function into  get_num_input indicating if
        the integer passes the appropriate checks.
        Function also outputs a string to stdout through printf specifying to the user what the
        conditions which were not met are. An example is "Number must be greater than 0".

When copying this function, programmer must change function name to something appropriate, the
condition checked in the "if" statement as a factor of input a, and the output string when the
condition is not met.


bool prototype_function(int a) {
    if (**INSERT CHECK HERE**) {
        return true;
    }
    else {
        printf(**INSERT ERROR STRING HERE**);
        return false;
    }
}
*/




#define PROCESS_STRING_LENGTH 30

int get_num_input(char* print_message, entry_check check_condition)
{
    char process[PROCESS_STRING_LENGTH] = {0};
    char *endpt;

    while(true) {
        printf("%s", print_message);
        fgets(process, PROCESS_STRING_LENGTH, stdin);
        int i = 0;
        while ((process[i] != 0) && (i < PROCESS_STRING_LENGTH)) {       //Null terminator
            if ((process[i] == '-' && ((process[i+1] >= '0') && (process[i+1] <= '9'))) ||
                (process[i] >= '0') && (process[i] <= '9')) {
                int number = strtol(&process[i], &endpt, 10);
                if (check_condition(number)) {
                    return number;
                }
                else {
                    break;
                }
            }
            i++;
        }
        printf("Error, that does not appear to be a valid number.\n");
    }
}


bool no_check(int a) {
    return true;
}



#endif // _NUM_INPUT_C_
