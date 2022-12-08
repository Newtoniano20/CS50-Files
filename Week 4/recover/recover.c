#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: recover [image]\n");
        return 1;
    }
    int writing = 0;
    uint8_t BUFFER[BLOCK_SIZE];
    int images = 0;
    FILE *f = fopen(argv[1], "r");
    FILE *img = fopen("000.jpg", "w");;
    char *filename = malloc(sizeof(char) * 8);
    while (fread(BUFFER, BLOCK_SIZE, 1, f))
    {
        if (BUFFER[0] == 0xff && BUFFER[1] == 0xd8 && BUFFER[2] == 0xff && ((BUFFER[3] & 0xf0) == 0xe0))
        {
            printf("Found One!\n");
            sprintf(filename, "%03i.jpg", images);
            images++;
            fclose(img);
            writing = 1;
            img = fopen(filename, "w");
        }
        if (writing)
        {
            fwrite(BUFFER, BLOCK_SIZE, 1, img);
        }
    }
    fclose(img);
    fclose(f);
    free(filename);
}