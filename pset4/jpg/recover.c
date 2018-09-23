/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdlib.h>
#include <stdio.h>

#define BUF_SIZE 512

int main()
{
    FILE* cardPtr = fopen("card.raw", "r");
    if (cardPtr == NULL) {
        printf("Could not open \"card.raw\".\n");
        return 1;
    }

    FILE* jpgPtr = NULL;
    char jpgName[8];
    unsigned char jpgID = 0;
    unsigned char buf[BUF_SIZE];

    while (!feof(cardPtr)) {
        fread(&buf, BUF_SIZE, 1, cardPtr);

        if (buf[0] == 0xFF && buf[1] == 0xD8 && buf[2] == 0xFF) {
            if (jpgPtr != NULL)
                fclose(jpgPtr);

            sprintf(jpgName, "%03d.jpg", jpgID);
            jpgID++;

            jpgPtr = fopen(jpgName, "w");
            if (jpgPtr == NULL) {
                fclose(cardPtr);
                printf("Could not create \"%s\".\n", jpgName);
                return 2;
            }
        }

        if (jpgPtr != NULL && !feof(cardPtr))
            fwrite(&buf, BUF_SIZE, 1, jpgPtr);
    }

    fclose(jpgPtr);
    fclose(cardPtr);
    return 0;
}
