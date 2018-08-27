#include <cs50.h>
#include <stdio.h>

int main(void) {
    int change = 0;
    do {
        change =  get_float("How much change is owed?: ") * 10000/100;
    } while (change < 0);

    int count = 0;

    count += change / 25;
    change %= 25;

    count += change / 10;
    change %= 10;

    count += change / 5;
    change %= 5;

    count += change;

    printf("%i\n", count);
}
