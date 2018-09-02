#include <cs50.h>
#include <stdio.h>
#include <string.h>

void printInitial(char key) {
    if (key == 32)
        return;
    if ((key > 96) && (key < 123))
        key -= 32;
    printf("%c", key);
}

int main() {
    string names = get_string("What is your names?:\n");
    printInitial(names[0]);
    for (int i = 0, n = strlen(names); i < n; i++) {
        if (names[i-1] == 32)
            printInitial(names[i]);
    }
    printf("\n");
}