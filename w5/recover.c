#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BUFF_SIZE 512

int main(void)
{
    FILE *inptr = fopen("card.raw", "r");
    
    if (inptr == NULL)
    {
        printf("Could not open card.raw file\n");
        return 1;
    }

    uint8_t buff[BUFF_SIZE];
    
    int count = 0;
    int writing = 0;

    FILE *out;
    while (fread(&buff, BUFF_SIZE, 1, inptr) == 1) {
        if (buff[0] == 0xff && buff[1] == 0xd8 && buff[2] == 0xff && (buff[3] & 0xe0) == 0xe0) {
            if (writing) {
                fclose(out); 
            } else {
                writing = 1;
            }
            char *title = malloc(sizeof(char) * 7 + 1);    
            sprintf(title, "%03d.jpg", count);
            out = fopen(title, "w");
            count++;
        } 

        if (writing) {
            fwrite(&buff, BUFF_SIZE, 1, out);
        }
    }
    fclose(out); 
    fclose(inptr);
    return 0;
}

