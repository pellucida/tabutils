
DEFINES	= -Delt_t=uint8_t
INCLUDES	= -I..

CFLAGS	+= $(INCLUDES) $(DEFINES) 

DIRS	= errors utils vec tabset tabutils

all:

	for dir in $(DIRS); do $(MAKE) -C $$dir CFLAGS='$(CFLAGS)' ; done

clean:
	for dir in $(DIRS); do $(MAKE) -C $$dir $@; done

distclean: clean
	$(MAKE) -C tabutils $@
	
	

