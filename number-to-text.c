/*
************************************************************************************************
number-to-text.c

This module details a simple function to translate an entered number into it's word equivalent.
************************************************************************************************

This module first takes from the user a number input through get_string_input which can isolate
the digits and a negative sign entered from additional surrounding text. The function also
returns a length integer used to keep track of the input.

The main loop then divides the entered string into groups of three and passes it to
print_hundreds with padded zeros if necessary. This function then outputs to stdout the word
equivalent number. The main loop checks how many groups of three are remaining and prints a
large number such as thousand or million following.

The entered number is never transformed into an integer as keeping the number divided by base
10 reduces mathematical calculations and the ASCII characters can easily be transformed into
their integer equivalent by taking away the ASCII offset. Not changing the entered number into
an integer also allows the module to calculate numbers up to ~10^29 if needed.

************************************************************************************************
*/



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LENGTH 30
#define ASCII_OFFSET 0x30


void flush_stdin(void);
uint8_t get_string_input(char* string_destination);
void print_hundreds(char* print_string);


const char* digits[] = {"", "one ", "two ", "three ", "four ", "five ", "six ", "seven ", "eight ", "nine "};
const char* teens[] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
const char* tens[] = {"", "", "twenty ", "thirty ", "forty ", "fifty ", "sixty ", "seventy ", "eighty ", "ninety "};
const char* order[] = {"","thousand, ", "million, ", "billion, ", "trillion, ", "quadrillion, ", "quintillion, ", "sextillion, ", "septillion, ", "octillion, ", "nonillion, "};
// Nonillion is 10^30 so with MAX_STRING_LENGTH at 30, hopefully it will never reach even with the largest entered number

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
            if ((('0' <= temp_string[i]) && (temp_string[i] <= '9')) ||     // Digit detected
                (('-' == temp_string[i]) && ('0' <= temp_string[i+1]) && (temp_string[i+1] <= '9')))    // Minus followed by digit
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
    // Print Hundreds
    if ('0' !=print_string[0])
    {
        printf("%shundred ", digits[(print_string[0] - ASCII_OFFSET)]);
    }
    // Print connecting "and" if non-zero digit in hundreds and tens or ones
    if (('0' != print_string[0]) && (('0' != print_string[1]) || ('0' != print_string[2])))
    {
        printf("and ");
    }
    // Special case for teens, use ones digit as reference
    if ('1' == print_string[1])
    {
        printf("%s ",teens[(print_string[2]- ASCII_OFFSET)]);
    }
    else
    {
        // Non need to check if either digit is non-zero as appropriate string array will not print anything at zero
        printf("%s%s",tens[(print_string[1]- ASCII_OFFSET)], digits[(print_string[2]- ASCII_OFFSET)]);
    }
}




int main()
{
    char num_string[MAX_STRING_LENGTH] = {0};

    uint8_t length = get_string_input(num_string);

    uint8_t i = 0;              // String pointer

    // Check if number is negative, print as such, and then increment the string pointer
    if ('-' == num_string[0])
    {
        printf("negative ");
        i++;
    }

    char pass_string[4] = {0};                       // Pass 3 digits + null terminator at a time through this string
    uint8_t remainder = ((length-i)%3);

    // Main loop which iterates through every three digits and passes them to print_hundreds
    while (0 < (length-i))
    {
        if (0 == remainder)
        {
            pass_string[0] = num_string[i++];       // Pass three digits if all three are within num_string
            pass_string[1] = num_string[i++];
            pass_string[2] = num_string[i++];
        }
        else
        {
            pass_string[0] = '0';                   // Pass one or two digits depending on remainder and fill the rest with zeros
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
            remainder = 0;                          // Clear remainder to prevent it causing issues
        }
        print_hundreds(pass_string);

        // Print the corresponding large number if pass_string was not all zero
        if (('0' != pass_string[0]) && ('0' != pass_string[1]) && ('0' != pass_string[2]))
        {
            printf("%s", order[(length-i)/3]);
        }


    }

    return 0;
}



