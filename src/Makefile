#
# @(#) Makefile
#
DEFINES	=	-Delt_t=uint16_t
INCLUDES	= -I$(PWD)

EXTRA	= -D_GNU_SOURCE -DHAVE_BASENAME -DHAVE_PROGRAM_INVOCATION_SHORT_NAME
CFLAGS	+= -g -Wall
# CFLAGS	+= -DVEC_EXPOSED
# CFLAGS	+= -DVEC_UNSAFE
CFLAGS	+= $(INCLUDES) $(DEFINES) 
CFLAGS	+= $(EXTRA)

WORK	= work

OBJ	= errors.o tabset.o tabset_errors.o tabutils_errors.o utils.o vec.o vec_errors.o
PROGS	= detab entab

vpath %.c $(PWD)/vec $(PWD)/utils $(PWD)/errors $(PWD)/tabset $(PWD)/tabutils

MFLAGS	= -C $(WORK) -f $(PWD)/Makefile

all:
	if [ ! -d $(WORK) ]; then mkdir $(WORK); fi
	if [ -d $(WORK) ]; then  $(MAKE) $(MFLAGS) _$@ ; fi
	
clean:
	if [ -d $(WORK) ]; then $(MAKE) $(MFLAGS) _$@ ; fi

distclean:
	if [ -d $(WORK) ]; then $(MAKE) $(MFLAGS) _$@ ; rmdir $(WORK); fi

_all:	$(OBJ) $(PROGS)
	

detab:	detab.o $(OBJ)

entab:	entab.o $(OBJ)

_distclean: _clean
	rm -f detab entab

_clean:	
	rm -f *.o 
	

detab.o: detab.c $(PWD)/errors/errors.h $(PWD)/bitfields/bitfields.h $(PWD)/vec/vec.h \
 $(PWD)/utils/utils.h $(PWD)/tabset/tabset.h

entab.o: entab.c $(PWD)/errors/errors.h $(PWD)/bitfields/bitfields.h \
 $(PWD)/utils/utils.h $(PWD)/tabset/tabset.h $(PWD)/vec/vec.h \
 $(PWD)/tabutils/tabutils_errors.h

errors.o: errors.c $(PWD)/bitfields/bitfields.h $(PWD)/errors/errors.h \
 $(PWD)/utils/utils.h $(PWD)/vec/vec_errors.h $(PWD)/tabset/tabset_errors.h \
 $(PWD)/tabutils/tabutils_errors.h

tabset.o: tabset.c $(PWD)/utils/utils.h $(PWD)/errors/errors.h \
 $(PWD)/bitfields/bitfields.h $(PWD)/mem/new.h $(PWD)/vec/vec.h $(PWD)/tabset/tabset.h \
 $(PWD)/tabset/tabset_errors.h

tabset_errors.o: tabset_errors.c $(PWD)/errors/errors.h \
 $(PWD)/bitfields/bitfields.h $(PWD)/tabset/tabset_errors.h

tabutils_errors.o: tabutils_errors.c $(PWD)/errors/errors.h \
 $(PWD)/bitfields/bitfields.h $(PWD)/tabutils/tabutils_errors.h

utils.o: utils.c $(PWD)/errors/errors.h $(PWD)/bitfields/bitfields.h \
 $(PWD)/utils/utils.h

vec.o: vec.c $(PWD)/errors/errors.h $(PWD)/bitfields/bitfields.h $(PWD)/mem/new.h \
 $(PWD)/mem/policy_size.h $(PWD)/vec/vec.h $(PWD)/vec/vec_errors.h

vec_errors.o: vec_errors.c $(PWD)/errors/errors.h $(PWD)/bitfields/bitfields.h \
 $(PWD)/vec/vec_errors.h
