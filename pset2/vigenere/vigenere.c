#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[]) {
    if (argc != 2) {
        printf("Usage: ./vigenere k\n");
        return 1;
    }

    string key = argv[1];
    int keyLength = strlen(key);

    for (int i = 0; i < keyLength; i++) {
        if (!isalpha(key[i])) {
            printf("The key must contain characters a-z or A-Z\n");
            return 1;
        }
        if (islower(key[i]))
            key[i] -= 32;
    }

    int offset = 0;
    string text = get_string("Enter the text for encryption with the Vigenere cipher:\n");
    for (int i = 0, textLength = strlen(text); i < textLength; i++) {
        if (!isalpha(text[i]))
            offset++;
        if (isupper(text[i]))
            text[i] = (text[i] + key[(i - offset) % keyLength] - 130) % 26 + 65;
        if (islower(text[i]))
            text[i] = (text[i] + key[(i - offset) % keyLength] - 162) % 26 + 97;
    }

    printf("ciphertext: %s\n", text);
    return 0;
}
