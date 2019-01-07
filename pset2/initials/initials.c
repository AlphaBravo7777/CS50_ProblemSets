#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main()
{
    string names = get_string("What is your names?:\n");

    if (!isblank(names[0]))
        printf("%c", toupper(names[0]));

    for (int i = 0, n = strlen(names); i < n; i++) {
        if (isblank(names[i-1]) && !isblank(names[i]))
            printf("%c", toupper(names[i]));
    }

    printf("\n");
}
