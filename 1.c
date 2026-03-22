#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: ./volume input output factor\n");
        return 1;
    }

    FILE *infile = fopen(argv[1], "rb");
    if (infile == NULL)
    {
        printf("Could not open input file.\n");
        return 1;
    }

    FILE *outfile = fopen(argv[2], "wb");
    if (outfile == NULL)
    {
        fclose(infile);
        printf("Could not create output file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    uint8_t header[44];
    fread(header, 1, 44, infile);
    fwrite(header, 1, 44, outfile);

    int16_t sample;

    while (fread(&sample, sizeof(int16_t), 1, infile) == 1)
    {
        sample = sample * factor;
        fwrite(&sample, sizeof(int16_t), 1, outfile);
    }

    fclose(infile);
    fclose(outfile);
    return 0;
}