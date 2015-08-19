#include "stdio.h"
#include "stdlib.h"

int main(int argc, char const *argv[]) {

        FILE *fd = fopen(argv[1], "rb");

        if(fd)
        {
                fseek(fd, 0, SEEK_END);
                size_t len = ftell(fd);
                fseek(fd, 0, SEEK_SET);

                char *data = malloc(len * sizeof(char));
                if(fread(data, sizeof(char), len, fd))
                {
                        unsigned int *dataInt = data;
                        unsigned int key = strtoul(argv[2], NULL, 16);
                        unsigned int maybePrime = (key & 0xFE) + 1;
                        if(maybePrime % 3 == 0) maybePrime += 2;
                        if(maybePrime < 3)maybePrime *= 241;
                        
                        for(int i = 0; i < len/sizeof(int); i++)
                        {
                                printf("%08x,", dataInt[i]);
                                dataInt[i] ^= key;
                                printf("%08x, %08x\n", dataInt[i], key);
                                key = (key * key % maybePrime);
                                if(key < 3) key+=3;
                        }
                }else{
                        return -1;
                }
                fclose(fd);

                fd = fopen(argv[3], "wb");
                if(fd)
                {
                        fwrite(data, sizeof(char), len, fd);
                        fclose(fd);
                }else{
                        return -1;
                }
                free(data);
        }else{
                return -1;
        }


        return 0;
}
