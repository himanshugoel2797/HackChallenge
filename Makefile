TARGET=hackme

PASSWORD_A=0x68647361
PASSWORD_B=0x00646461
PASSWORD_C=0x699a8c76


CC=gcc

CFLAGS=-Wall -Wextra -O0
LIBS=-lm

first: CFLAGS=-Wall -Wextra -O0 -ffreestanding -fPIC -Tlinker.x -nostdlib


OBJS=main.o md5.o
EXTERN_OBJS=passCheckA.o passCheckB.o passCheckC.o


.PHONY:clean all

all:first

xorEnc:
	$(CC) $(CFLAGS) xorEncrypter.c -o xorEnc

first:clean $(EXTERN_OBJS)
	#Compile all the parts
	$(CC) $(CFLAGS) passCheckA.o -o passCheckA.elf
	$(CC) $(CFLAGS) passCheckB.o -o passCheckB.elf
	$(CC) $(CFLAGS) passCheckC.o -o passCheckC.elf
	objcopy -O binary passCheckA.elf passCheckA.bin
	objcopy -O binary passCheckB.elf passCheckB.bin
	objcopy -O binary passCheckC.elf passCheckC.bin
	$(MAKE) xorEnc
	./xorEnc passCheckA.bin $(PASSWORD_A) passCheckA.xo
	./xorEnc passCheckB.bin $(PASSWORD_B) passCheckB.xo
	./xorEnc passCheckC.bin $(PASSWORD_C) passCheckC.xo
	touch partAData.h
	touch partBData.h
	touch partCData.h
	xxd -i passCheckA.xo > partAData.h
	xxd -i passCheckB.xo > partBData.h
	xxd -i passCheckC.xo > partCData.h
	$(MAKE) $(TARGET)

$(TARGET):$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) $(EXTERN_OBJS) $(EXTERN_OBJS:.o=.xo) $(EXTERN_OBJS:.o=.bin) $(EXTERN_OBJS:.o=.elf) xorEnc
