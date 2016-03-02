/*
************************************************************************************************
num_input.c

This file details a simple input function that can be used to obtain a user entered number.
************************************************************************************************

The primary function called is get_num_input that takes two parameters. The first is a string
to be printed to stdout indicating to the user what they would like to be entered, and the
second is a function pointer based off the entry_check type defined below.

get_num_input takes these two parameters and outputs an integer that the user enters when it
meets the appropriate conditions.

If the user does not want to set a condition function, the function no_check can be passed
and any valid number entered will be returned.



entry_check is a function type that takes one integer and returns a boolean output. A prototype
function has been included below which the programmer can copy and use in their own functions.


**********************************************************************************************
Update 02-03-16
Added "constant" to variables given to checks
Added a positive integer check "positive_check" to reduce rewriting such a common check in other modules
Added check to see if last character in string is not null-terminator indicating an overflow
*/



#ifndef _NUM_INPUT_C_
#define _NUM_INPUT_C_


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef bool (*entry_check)(const int a);

void flush_stdin(void);
bool positive_check(const int a);
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


bool prototype_function(const int a) {
    if (**INSERT CHECK HERE**) {
        return true;
    }
    else {
        printf(**INSERT ERROR STRING HERE**);
        return false;
    }
}
*/




// Canned functions that ask for a number from STDin, return if number is non-zero,
// and flush STDin and loop otherwise.

// Only called if string overflows
void flush_stdin(void)
{
    int c;
    while((c = getchar()) != EOF)
        if (c == '\n')
            break;
}



#define PROCESS_STRING_LENGTH 30

int get_num_input(char* print_message, entry_check check_condition)
{


    while(true) {
        char process[PROCESS_STRING_LENGTH] = {0};
        char *endpt;
        printf("%s", print_message);
        fgets(process, PROCESS_STRING_LENGTH, stdin);

        //If last character is not the initialised zero or a similar null terminator, string was too long
        if (process[(PROCESS_STRING_LENGTH-2)] != 0)
        {
            process[0] = 0;         // Set first character to null terminator, below loop will not run
            printf("Error, too many characters entered.\n");
            flush_stdin();
        }

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

// No check on the value
bool no_check(const int a) {
    return true;
}


// Only constraint is that the number cannot be negative.
bool positive_check(const int a) {
    if (0 < a) {
        return true;
    }
    else {
        printf("Error, number must be positive integer\n");
        return false;
    }
}


#endif // _NUM_INPUT_C_
