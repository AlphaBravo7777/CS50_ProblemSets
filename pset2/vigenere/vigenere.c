#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CONVERSION(a) (text[i] = (text[i] - (a) + keyWord[(i - offset) % keyLength]) % 26 + (a))

int main(int argc, string argv[])
{
    if (argc != 2) {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }

    string keyWord = argv[1];
    int keyLength = strlen(keyWord);

    for (int i = 0; i < keyLength; i++) {
        if (!isalpha(keyWord[i])) {
            printf("invalid keyword\n");
            return 1;
        }

        keyWord[i] = toupper(keyWord[i]) - 'A';
    }

    string text = get_string("plaintext: ");

    for (int i = 0, offset = 0; text[i]; i++) {
        if (isupper(text[i]))
            CONVERSION('A');
        else if (islower(text[i]))
            CONVERSION('a');
        else
            offset++;
    }

    printf("ciphertext: %s\n", text);
    return 0;
}
