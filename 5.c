#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long number = get_long("Number: ");
    long temp = number;

    int sum = 0;
    int position = 0;
    int length = 0;

    while (temp > 0)
    {
        int digit = temp % 10;

        if (position % 2 == 0)
        {
            sum += digit;
        }
        else
        {
            int doubled = digit * 2;
            sum += doubled / 10 + doubled % 10;
        }

        temp /= 10;
        position++;
        length++;
    }

    long start = number;
    while (start >= 100)
    {
        start /= 10;
    }

    int first_two = start;
    int first_one = first_two / 10;

    if (sum % 10 != 0)
    {
        printf("INVALID\n");
    }
    else if (length == 15 && (first_two == 34 || first_two == 37))
    {
        printf("AMEX\n");
    }
    else if (length == 16 && (first_two >= 51 && first_two <= 55))
    {
        printf("MASTERCARD\n");
    }
    else if ((length == 13 || length == 16) && first_one == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}