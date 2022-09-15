#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Usage ./recover file\n");
        return 1;
    }
    FILE* card = fopen(argv[1], "r");
    if(card == NULL)
    {
        printf("cannot read file\n");
        return 1;
    }


    int counter = 0;
    BYTE data[512];

    //create out put file
    char filename[100];
    sprintf(filename, "%03i.jpg", counter);
    FILE* ojpg = fopen(filename, "w");

    while(fread(data, sizeof(BYTE), 1, card) != EOF)
    {
        if ((data[0] == 0xff) && (data[1] == 0xd8) && (data[2] == 0xff) && ((data[3] & 0xf0) == 0xe0))
        {
            if(counter == 0)
            {
                fwrite(data, sizeof(BYTE), 512, ojpg);
                counter++;
            }
            else
            {
                fclose(ojpg);
                sprintf(filename, "%03i.jpg", counter);
                ojpg = fopen(filename, "w");
                fwrite(data, sizeof(BYTE), 512, ojpg);
                counter++;
            }
        }
        else if(counter != 0)
        {
            fwrite(data, sizeof(BYTE), 512, ojpg);
        }
        else
        {
            continue;
        }
    }
    fclose(ojpg);
    fclose(card);

}