
CFLAGS	+= -Wall -I.. -Delt_t=uint16_t -g

OBJ	= tabset.o tabset_errors.o

all:	$(OBJ)

clean:
	rm -f *.o *.gch


tabset.o: tabset.c ../utils/utils.h ../errors/errors.h \
 ../bitfields/bitfields.h ../mem/new.h ../vec/vec.h ../tabset/tabset.h \
 ../tabset/tabset_errors.h
tabset_errors.o: tabset_errors.c ../errors/errors.h \
 ../bitfields/bitfields.h ../tabset/tabset_errors.h

