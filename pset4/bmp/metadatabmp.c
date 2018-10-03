/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2) {
        printf("Usage: ./copy infile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[1];
    char *outfile = "metadatabmp.txt";

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL) {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL) {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
    bi.biBitCount != 24 || bi.biCompression != 0) {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    fprintf(outptr, "%s\n", infile);

    fprintf(outptr, "\n\nBITMAPFILE\n\n");
    fprintf(outptr, "bfType %X\n", bf.bfType);
    fprintf(outptr, "bfSize %i bytes\n", bf.bfSize);
    fprintf(outptr, "bfReserved1 %i\n", bf.bfReserved1);
    fprintf(outptr, "bfReserved2 %i\n", bf.bfReserved2);
    fprintf(outptr, "bfOffBits %i bytes\n", bf.bfOffBits);

    fprintf(outptr, "\n\nBITMAPINFO\n\n");
    fprintf(outptr, "biSize %i bytes\n", bi.biSize);
    fprintf(outptr, "biWidth %i pixels\n", bi.biWidth);
    fprintf(outptr, "biHeight %i pixels\n", bi.biHeight);
    fprintf(outptr, "biPlanes %i\n", bi.biPlanes);
    fprintf(outptr, "biBitCount %i bits/pixel\n", bi.biBitCount);
    fprintf(outptr, "biCompression %i\n", bi.biCompression);
    fprintf(outptr, "biSizeImage %i bytes\n", bi.biSizeImage);
    fprintf(outptr, "biXPelsPerMeter %i pixels/m\n", bi.biXPelsPerMeter);
    fprintf(outptr, "biYPelsPerMeter %i pixels/m\n", bi.biYPelsPerMeter);
    fprintf(outptr, "biClrUsed %i\n", bi.biClrUsed);
    fprintf(outptr, "biClrImportant %i\n", bi.biClrImportant);

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
