// UNFINISHED ALPHA
// ONLY PRINTS EACH SET OF THREE DIGITS AND CORRESPONDING ORDER OF MAGNITUDE

/* 
Completed:
    String input and number isolation
    Separation into groups of three digits
    Printing of order such as thousand, million etc after each group of 3 digits
    
Uncompleted:
    "print_hundreds" function printing each group of three numbers
    Error testing and better input sanitising
    Support for negative numbers
*/



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LENGTH 30


const char* order[] = {""," thousand, ", " million, ", " billion, ", " trillion, ", " quadrillion, ", "quintillion, "};

void flush_stdin(void)
{
    uint8_t c;
    while((c = getchar()) != EOF)
        if (c == '\n')
            break;
}



/* *****************************************************************************
get_string_input

Description:
    Asks the user to input a number and searches through the entered string for
    a the digits which make up a positive integer without spaces or commas.
Inputs:
    String pointer string_destination of length MAX_STRING_LENGTH
    User input through stdin
Outputs:
    String of digits to the pointer provided by string_destination
    Return uint8_t of the length of the string of digits
***************************************************************************** */
uint8_t get_string_input(char* string_destination)
{
    while(true) {
        printf("Please enter your number: ");
        char temp_string[MAX_STRING_LENGTH] = {0};
        fgets(temp_string, MAX_STRING_LENGTH, stdin);

        //If last character is not the initialised zero or a similar null terminator, string was too long
        if (0 != temp_string[(MAX_STRING_LENGTH-2)])
        {
            temp_string[0] = 0;         // Set first character to null terminator, below loop will not run
            printf("Error, too many characters entered.\n");
            flush_stdin();
        }


        uint8_t i = 0;
        while ((0 != temp_string[i]) && (MAX_STRING_LENGTH > i))
        {
            if (('0' <= temp_string[i]) && (temp_string[i] <= '9'))
            {
                uint8_t length = 1;
                while (('0' <= temp_string[i+length]) && ('9' >= temp_string[i+length]))
                {
                    length++;
                }
                memmove(string_destination, &temp_string[i], length);
                return length;
            }
            i++;
        }
        printf("Error, could not find a valid number.\n");


    }
}


/* *****************************************************************************
print_hundreds

Description:
    Takes three digits in a string pointer, looks them up in a corresponding
    string array, and then prints them to stdout. Strings are processed three
    digits at a time due to the east of adding an order of magnitude after every
    three digits.
Inputs:
    String pointer print_string which contains three digits to be printed
Outputs:
    Prints to stdout the passed string of digits in their full word format,
    three digits at a time.
***************************************************************************** */
void print_hundreds(char* print_string)
{

    // DEBUG
    printf("%s",print_string);

    // Full code to be completed

}




int main()
{
    char num_string[MAX_STRING_LENGTH] = {0};

    uint8_t length = get_string_input(num_string);

    // DEBUG
    printf("%s, length %u\n", num_string, length);


    uint8_t i = 0;                                  // String pointer
    char pass_string[4] = {0};                       // Pass 3 digits + null terminator at a time through this string
    uint8_t remainder = (length%3);

    // Main loop which iterates through every three digits and passes them to print_hundreds
    while (0 < (length-i))
    {
        if (0 == remainder)
        {
            pass_string[0] = num_string[i++];
            pass_string[1] = num_string[i++];
            pass_string[2] = num_string[i++];
        }
        else
        {
            pass_string[0] = '0';
            if (1 == remainder)
            {
                pass_string[1] = '0';
                pass_string[2] = num_string[i];
                i++;
            }
            else
            {
                pass_string[1] = num_string[i];
                pass_string[2] = num_string[i+1];
                i += 2;
            }
            remainder = 0;
        }
        print_hundreds(pass_string);

        if (0 < length-i)
        {
            printf("%s", order[(length-i)/3]);
        }

    }

    return 0;
}



