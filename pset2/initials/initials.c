#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

int main()
{
    string names = get_string();

    printf("%c", toupper(names[0]));
    for (int i = 0; names[i]; i++) {
        if (isblank(names[i]))
            printf("%c", toupper(names[i+1]));
    }

    printf("\n");
}
