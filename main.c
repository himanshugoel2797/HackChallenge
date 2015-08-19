#include "md5.h"
#include "partAData.h"
#include "partBData.h"
#include "partCData.h"
#include "lolyes.h"

#include <stdio.h>
#include <sys/mman.h>

int decryptAndLoad(void *loc, char *data, char **keyval, int argc, unsigned int len)
{
        unsigned int *target = (unsigned int*)loc;
        unsigned int *src = (unsigned int*)data;
        unsigned int key = *(unsigned int*)keyval[0];
        unsigned int maybePrime = (key & 0xFE) + 1;
        if(maybePrime % 3 == 0) maybePrime += 2;
        if(maybePrime < 3) maybePrime *= 241;

        for(int i = 0; i < len/sizeof(int); i++)
        {
                target[i] = src[i] ^ key;
                key = ((key * key) % maybePrime);
                if(key < 3) key += 3;
        }
        int (*func)(int, char**) = target;
        int result = func(argc, keyval);
        return result;
}

int main(int argc, char const *argv[]) {

        size_t size = 0x1000;
        void *mapLoc = mmap(NULL, size, PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
        char *enteredPass = 0, cpy[15];

        printf("Enter the password:\n");

        if(scanf("%ms", &enteredPass) == 1 && strlen(enteredPass) == 4)
        {
                strcpy(cpy, enteredPass);
                int result = decryptAndLoad(mapLoc, passCheckA_xo, &enteredPass, 0, passCheckA_xo_len);
                result = decryptAndLoad(mapLoc, passCheckB_xo, &enteredPass, result, passCheckB_xo_len);

                unsigned int *key = (unsigned int*)enteredPass;
                *key ^= *(unsigned int*)cpy;

                result = decryptAndLoad(mapLoc, passCheckC_xo, &enteredPass, result, passCheckC_xo_len);
                printf("Result: %s\n", (char*)mapLoc);
        }else{
                printf("Nop, go again scrub\n");
        }

        munmap(mapLoc, size);
        return 0;
}
