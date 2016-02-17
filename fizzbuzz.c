// FizzBuzz

// Write a function that outputs the numbers from 1 to 100, but
// with multiples of 3 replaced with "Fizz", multiples of 5
// replaced with "Buzz", and multiples of both 3 and 5 replaced
// with "FizzBuzz".

// Three functions were designed to complete this task, all taking
// a maximum argument (generally of 100) and returning an int of 0
// upon completion.
// One method uses simple branching in a foor loop, another passes
// a string pointer to a smaller function which then calculates
// similar to the first method, and the last uses constant arrays
// and a for loop without any "if" branches.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"


// fizzbuzz_1 outputs the expected result with the simplest branching
// code of the three functions.

// "i%15" is used in place of checking 3's remainder and then branching
// where both branches check the 5's remainder and double-up on code.
// As both 3 and 5 are prime numbers, any number which is a factor of both
// will also be a factor of their product, 15.

int fizzbuzz_1(int maximum)
{
    int i = 1;
    for (i = 1; i <= maximum; i++)
    {
        if (i % 15 == 0)
        {
            printf("FizzBuzz \n");
        }
        else if (i % 5 == 0)
        {
            printf("Buzz \n");
        }
        else if (i % 3 == 0)
        {
            printf("Fizz \n");
        }
        else printf("%i \n", i);
    }
    return 0;
}



// fizzbuzz_2 outputs the result by calling separate function fizzbuzz_2_check
// which takes a string pointer and an i value to be printed.

// fizzbuzz_2_check uses the same checking algorithm as in fizzbuzz_1, but
// instead copies the appropriate string to the string pointer it is passed.
// While this can be used as a more portable version of FizzBuzz passing strings
// to anywhere, it was mostly written for practice working with strings in C.

int fizzbuzz_2_check(char *str1, int num)
{
    if (num % 15 == 0)
    {
        strcpy(str1, "FizzBuzz");
    }
    else if (num % 5 == 0)
    {
        strcpy(str1, "Buzz");
    }
    else if (num % 3 == 0)
    {
        strcpy(str1, "Fizz");
    } else sprintf(str1, "%i", num);

    return 0;
}

int fizzbuzz_2(int maximum)
{
    char str1[10] = {0};

    int i = 1;
    for(i = 1; i <= maximum; i++)
    {
        fizzbuzz_2_check(&str1[0], i);
        printf("%s\n", str1);
    }

    return 0;
}



// fizzbuzz_3 outputs the result by using the modulus operator to point to a value
// in a constant array of strings and prints Fizz or Buzz when appropriate.

// The modulus operator of 3 will only output from 0-2 and for 5 it will output 0-5.
// As the appropriate string should be printed when the modulus is zero, an array with
// the string at [0] and null strings in all other places will give the desired result.

// As we do not want to print the number when Fizz or Buzz is printed, a similar constant
// array with 0 at [0] and 1 in all other places is used. When both of these arrays are
// multiplied by the first character in the number string, a non-multiple of 3 or 5 will
// not be changed while a multiple will have the first character changed into a
// null character or null terminator ('\0') and will cause the print function to read an
// empty string.

// The goal of this function was to create FizzBuzz without using "if" branches. While it
// is not as elegant or memory efficient as other solutions, it was an interesting exercise.

int fizzbuzz_3(int maximum)
{
    const char fizz_array[3][5] = {"Fizz", "", ""};
    const char fizz_cancel[3] = {0,1,1};

    const char buzz_array[5][5] = {"Buzz", "", "", "", ""};
    const char buzz_cancel[5] = {0,1,1,1,1};

    char num[4] = "";

    int i = 1;
    for (i = 1; i <= maximum; i++)
    {
        sprintf(num, "%i", i);
        num[0] *= (fizz_cancel[i%3] * buzz_cancel[i%5]);
        printf("%s", num);
        printf("%s", fizz_array[i%3]);
        printf("%s\n", buzz_array[i%5]);
    }

    return 0;

}


int main()
{
    //printf("Hello world!\n");

    fizzbuzz_1(100);

    fizzbuzz_2(100);

    fizzbuzz_3(100);

    return 0;
}
