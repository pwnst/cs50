#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        printf("Usage: ./copy infile outfile\n");
        return 1;
    }

    int resize = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];

    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    int input_padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    int header_size = sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER);

    int old_width = bi.biWidth;
    int old_height = bi.biHeight;
    int new_width = old_width * resize;
    int new_height = old_height * resize;

    int padding =  (4 - (new_width * sizeof(RGBTRIPLE)) % 4) % 4;
    int line_width =  input_padding + sizeof(RGBTRIPLE) * old_width;
    
    int image_size = new_width * abs(new_height) * sizeof(RGBTRIPLE) + padding * abs(new_height);

    bf.bfSize = image_size + header_size;
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    bi.biWidth = new_width;
    bi.biHeight = new_height;
    bi.biSizeImage = image_size;

    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);


    for (int i = 0, biHeight = abs(old_height); i < biHeight; i++)
    {
        int h_count = resize;   
        while (h_count > 0) {
            for (int j = 0; j < old_width; j++)
            {
                RGBTRIPLE *triple = malloc(sizeof(RGBTRIPLE));
                fread(triple, sizeof(RGBTRIPLE), 1, inptr);
                
                int w_count = resize;
                while (w_count > 0) {
                    fwrite(triple, sizeof(RGBTRIPLE), 1, outptr);
                    w_count--;
                }
                free(triple);
            }
            
            fseek(inptr, input_padding, SEEK_CUR);

            for (int k = 0; k < padding; k++)
            {
                fputc(0x00, outptr);
            }
            
            fseek(inptr, -line_width, SEEK_CUR);
            h_count--;
        }
        fseek(inptr, line_width, SEEK_CUR);
    }

    fclose(inptr);
    fclose(outptr);
    return 0;
}
