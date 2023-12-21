
CFLAGS	+= -I$(PWD)/.. -I$(PWD)/../.. -Delt_t=uint8_t -g

OBJ	= tabset.o tabset_errors.o

all:	$(OBJ)

clean:
	rm -f *.o *.gch


tabset.o: tabset.c $(PWD)/../../utils/utils.h $(PWD)/../../errors/errors.h \
 $(PWD)/../../bitfields/bitfields.h $(PWD)/../../mem/new.h $(PWD)/../../vec/vec.h $(PWD)/../tabset/tabset.h \
 $(PWD)/../tabset/tabset_errors.h
tabset_errors.o: tabset_errors.c $(PWD)/../../errors/errors.h \
 $(PWD)/../../bitfields/bitfields.h $(PWD)/../tabset/tabset_errors.h

