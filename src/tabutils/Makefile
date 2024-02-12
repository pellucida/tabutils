
CFLAGS	+= -Wall -I.. -g -Delt_t=uint8_t 

OBJ	= detab.o entab.o tabutils_errors.o

all:	$(OBJ)


clean:
	rm -f *.o a.out

distclean: clean

detab.o: detab.c ../errors/errors.h ../bitfields/bitfields.h ../vec/vec.h \
 ../utils/utils.h ../tabset/tabset.h

entab.o: entab.c ../errors/errors.h ../bitfields/bitfields.h \
 ../utils/utils.h ../tabset/tabset.h ../vec/vec.h \
 ../tabutils/tabutils_errors.h

tabutils_errors.o: tabutils_errors.c ../errors/errors.h \
 ../bitfields/bitfields.h ../tabutils/tabutils_errors.h
