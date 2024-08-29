#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

WAVHEADER bufin;

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    char *input = argv[1];
    FILE *inptr = fopen(input, "r");
    if (inptr == NULL)
    {
        printf("File could not open\n");
        return 2;
    }

    // Read header
    // TODO #3
    fread(&bufin, sizeof(WAVHEADER), 1, inptr);

    // Use check_format to ensure WAV format
    // TODO #4
    if (!check_format(bufin))
    {
        fclose(inptr);
        printf("Unsupported file format\n");
        return 3;
    }

    // Open output file for writing
    // TODO #5
    char *output = argv[2];
    FILE *outptr = fopen(output, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        printf("File could not create\n");
        return 4;
    }

    // Write header to file
    // TODO #6
    fwrite(&bufin, sizeof(WAVHEADER), 1, outptr);

    // Use get_block_size to calculate size of block
    // TODO #7
    int block_size = get_block_size(bufin);

    // Write reversed audio to file
    // TODO #8
    BYTE arr[block_size];
    fseek(inptr, 0, SEEK_END);
    int block_num = ((ftell(inptr) - sizeof(WAVHEADER)) / block_size);
    for (int i = block_num - 1; i >= 0; i--)
    {
        fseek(inptr, sizeof(WAVHEADER) + i * block_size, SEEK_SET);
        fread(arr, block_size, 1, inptr);
        fwrite(arr, block_size, 1, outptr);
    }
    fclose(outptr);
    fclose(inptr);
}

int check_format(WAVHEADER header)
{
    // TODO #4
    char format[4] = {'W', 'A', 'V', 'E'};
    for (int i = 0; i < 4; i++)
    {
        if (bufin.format[i] == format[i])
        {
            return 1;
        }
    }
    return 0;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    int size = 0;
    size = ((bufin.numChannels) * (bufin.bitsPerSample / 8));
    return size;
}