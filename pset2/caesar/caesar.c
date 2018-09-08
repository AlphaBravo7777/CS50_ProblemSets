#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[]) {
    if (argc != 2) {
        printf("Usage: ./caesar k\n");
        return 1;
    }

    for (int i = 0, argvLength = strlen(argv[1]); i < argvLength; i++) {
        if (!isdigit(argv[1][i])) {
            printf("The key must be an unsigned integer type\n");
            return 1;
        }
    }

    int key = atoi(argv[1]);
    string text = get_string("Enter the text for encryption with the Caesar cipher:\n");

    for (int i = 0, textLength = strlen(text); i < textLength; i++) {
        if (isupper(text[i]))
            text[i] = (text[i] - 'A' + key) % 26 + 'A';
        if (islower(text[i]))
            text[i] = (text[i] - 'a' + key) % 26 + 'a';
    }

    printf("ciphertext: %s\n", text);
    return 0;
}
