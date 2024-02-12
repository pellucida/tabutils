
CFLAGS	+= -Wall -g -I.. -Delt_t=uint8_t

all:	utils.o

clean:
	rm -f *.o *.gch

utils.o: utils.c ../errors/errors.h ../bitfields/bitfields.h \
 ../utils/utils.h
