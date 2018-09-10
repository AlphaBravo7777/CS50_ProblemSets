#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int change = 0;
    do {
        change =  get_float("How much change is owed?: ") * 10000/100;
    } while (change < 0);

    int count = 0;
    while (change > 0) {
        if (change >= 25)
            change -= 25;
        else if (change >= 10)
            change -= 10;
        else if (change >= 5)
            change -= 5;
        else if (change >= 1)
            change -= 1;

        count++;
    }

    printf("%i\n", count);
}
