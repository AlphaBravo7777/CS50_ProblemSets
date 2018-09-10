#include <cs50.h>
#include <stdio.h>

int main()
{
    int h = 0, height = 0;

    do {
        height = get_int("height: ");
        if (height == 0)
            return 0;
    } while ((height < 1) || (height > 23));

    do {
        for (int i = 0; i < height - (h+1); i++)
            printf(" ");
        for (int i = 0; i < h; i++)
            printf("#");
        
        printf("##\n");
        h++;
    } while (h != height);
}
