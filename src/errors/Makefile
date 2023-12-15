
CFLAGS	+= -g -I.. # -DUSE_SYS_ERRLIST

OBJ	= errors.o

all:	$(OBJ)

clean:
	rm -f *.o *.gch

errors.o: errors.c ../bitfields/bitfields.h ../errors/errors.h
