#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover card.raw\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "rb");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    uint8_t block[512];
    FILE *img = NULL;
    char name[8];
    int jpgCount = 0;

    while (fread(block, 1, 512, input) == 512)
    {
        bool is_jpg_start = block[0] == 0xff &&
                            block[1] == 0xd8 &&
                            block[2] == 0xff &&
                            (block[3] & 0xf0) == 0xe0;

        if (is_jpg_start)
        {
            if (img != NULL)
            {
                fclose(img);
            }

            sprintf(name, "%03i.jpg", jpgCount);
            img = fopen(name, "wb");
            jpgCount++;
        }

        if (img != NULL)
        {
            fwrite(block, 1, 512, img);
        }
    }

    if (img != NULL)
    {
        fclose(img);
    }

    fclose(input);
    return 0;
}