// A simple command line calculator program designed to make use of function pointers in an array rather than using
// a switch-case statement.

// Function pointers in this fashion can be incredibly useful in state machines that run on cycles as the numerous
// if or switch-case statements can make the code very messy while this reduces the problem down to a simple pointer.
// This model is also useful for event-based processes as the appropriate event can be found and run significantly
// faster than as with any other model.


// While function prototypes and constant declarations are usually in a separate header file, they have been included
// here for neatness on Github.

// Update 25-02-16
// Changed get_num_input function to use fgets and strtol rather than scanf. The benefits of this are that the program
// no longer crashes when the user enters a letter before a number. Function can now find a single number amongst a
// string of characters. While it still cannot receive non-integers and does not recognise numbers separated by a comma,
// this is still a massive improvement.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int addition(int a, int b);
int subtraction(int a, int b);
int multiplication(int a, int b);
int division(int a, int b);

#define total_expressions 4
const char expressions_list[] = {'+', '-', '*', '/'};

const int (*expression_functions[total_expressions])(int x, int y) = {addition, subtraction, multiplication, division};
// Notes for self:
// Must define this as a pointer array and include the arguments it is passed
// Can pass to function is you use typedef with this kind of function declaration including returning value and arguments
// Must have function prototypes prior to setting values of array


// Typedef is best done without array functions and just including the arguments and return value
typedef int (*calculate_func)(int a, int b);



// Canned functions that ask for a number from STDin, return if number is non-zero,
// and flush STDin and loop otherwise.
void flush_stdin(void)
{
    int c;
    while((c = getchar()) != EOF)
        if (c == '\n')
            break;
}


// Useful function for checking if the inputted character is in an array.
// Global constant array "expressions_list" can be any list of characters and function
// will still work correctly.
int get_expression(char* print_message){
    char expression;
    while(true) {
        printf("%s", print_message);
        expression = getchar();
        int i;
        for (i=0; i<total_expressions; i++) {
            if (expression == expressions_list[i]) {
                flush_stdin();
                return i;
            }
        }
        printf("Oops, it appears that isn't a valid expression. Please try again.\n");
        flush_stdin();
    }
}

#define new_get_num
#ifndef new_get_num

// Obsolete, crashes when user enters a letter before a number
int get_num_input(char* print_message)
{
    int number = 0;
    while(true) {
        printf("%s", print_message);
        if ((scanf(" %d", &number)) >0)
            return number;
        printf("Error, that is not a valid number. Please try again\n");
        flush_stdin();
    }
}
#else
#define PROCESS_STRING_LENGTH 30
int get_num_input(char* print_message)
{
    char process[PROCESS_STRING_LENGTH] = {0};
    char *endpt;

    while(true) {
        printf("%s", print_message);
        fgets(process, PROCESS_STRING_LENGTH, stdin);
        int i = 0;
        while (process[i] != 0) {       //Null terminator
            if ((process[i] >= '0') && (process[i] <= '9')) {
                return strtol(&process[i], &endpt, 10);
            }
            i++;
        }
        printf("Error, that does not appear to be a valid number.\n");
    }
}

#endif // new_get_num


// Simple expression functions, just an example that can be replaced with anything else
int addition(int a, int b){
    return a + b;
}
int subtraction(int a, int b){
    return a - b;
}
int multiplication(int a, int b){
    return a * b;
}
int division(int a, int b){
    return a / b;
}


int calculate(int a, int b, calculate_func expression)
{
    return expression(a,b);
}





int main()
{

    int expression = get_expression("Please enter your expression:");
    int first_num = get_num_input("Please enter your first number:");
    int second_num = get_num_input("Please enter your second number:");

    // Using the typedef and the calculate function to pass the correct function pointer to the function
    int result = calculate(first_num, second_num, expression_functions[expression]);

    // Another more direct way if it is not necessary to pass the function pointer
    // int result = (*expression_functions[expression])(first_num, second_num);

    printf ("%d %c %d = %d", first_num, expressions_list[expression], second_num, result);

    return 0;
}


