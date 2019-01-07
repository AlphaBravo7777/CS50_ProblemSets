#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    if (argc != 2) {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    for (int i = 0; argv[1][i]; i++) {
        if (!isdigit(argv[1][i])) {
            printf("Key must be a non-negative integer.\n");
            return 1;
        }
    }

    int key = atoi(argv[1]);
    string text = get_string("plaintext: ");

    for (int i = 0; text[i]; i++) {
        if (isupper(text[i]))
            text[i] = (text[i] - 'A' + key) % 26 + 'A';
        if (islower(text[i]))
            text[i] = (text[i] - 'a' + key) % 26 + 'a';
    }

    printf("ciphertext: %s\n", text);
    return 0;
}
