#include <cs50.h>
#include <stdio.h>

int main()
{
    int minutes = get_int("waterminutes: ");
    printf("bottles: %i\n", 12 * minutes);
}
