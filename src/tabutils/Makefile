
SUPPORT	=  ../utils/utils.o ../tabset/tabset.o ../vec/vec.o
SUPPORT	+= ../errors/errors.o ../tabutils/tabutils_errors.o ../tabset/tabset_errors.o ../vec/vec_errors.o

CFLAGS	+= -I.. -g -Delt_t=uint8_t 
PROGS	+= entab detab

all:	$(PROGS)


clean:
	rm -f *.o a.out

distclean: clean
	rm -f $(PROGS)

entab:	entab.o  $(SUPPORT)
detab:	detab.o  $(SUPPORT)

detab.o: detab.c ../errors/errors.h ../bitfields/bitfields.h ../vec/vec.h \
 ../utils/utils.h ../tabset/tabset.h
entab.o: entab.c ../errors/errors.h ../bitfields/bitfields.h \
 ../utils/utils.h ../tabset/tabset.h ../vec/vec.h \
 ../tabutils/tabutils_errors.h
tabutils_errors.o: tabutils_errors.c ../errors/errors.h \
 ../bitfields/bitfields.h ../tabutils/tabutils_errors.h

