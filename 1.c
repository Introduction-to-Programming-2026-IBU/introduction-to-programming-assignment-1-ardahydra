#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool valid_key(string key);

int main(int argc, string argv[])
{
    if (argc != 2 || !valid_key(argv[1]))
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];
    string plaintext = get_string("plaintext:  ");

    printf("ciphertext: ");

    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        char c = plaintext[i];

        if (isupper(c))
        {
            int index = c - 'A';
            printf("%c", toupper(key[index]));
        }
        else if (islower(c))
        {
            int index = c - 'a';
            printf("%c", tolower(key[index]));
        }
        else
        {
            printf("%c", c);
        }
    }

    printf("\n");
    return 0;
}

bool valid_key(string key)
{
    if (strlen(key) != 26)
    {
        return false;
    }

    for (int i = 0; i < 26; i++)
    {
        if (!isalpha(key[i]))
        {
            return false;
        }

        for (int j = i + 1; j < 26; j++)
        {
            if (tolower(key[i]) == tolower(key[j]))
            {
                return false;
            }
        }
    }

    return true;
}