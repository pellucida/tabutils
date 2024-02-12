
CFLAGS	+= -Wall -I.. -g -Delt_t=uint8_t 

OBJ	= vec.o vec_errors.o

all:	$(OBJ)

clean:	
	rm -f *.o *.gch

vec.o: vec.c ../errors/errors.h ../bitfields/bitfields.h ../mem/policy_size.h \
 ../mem/new.h ../vec/vec.h ../vec/vec_errors.h
vec_errors.o: vec_errors.c ../errors/errors.h ../bitfields/bitfields.h \
 ../vec/vec_errors.h
