
DEFINES	= -Delt_t=uint8_t
INCLUDES	= -I..

EXTRA	= -D_GNU_SOURCE -DHAVE_BASENAME -DHAVE_PROGRAM_INVOCATION_SHORT_NAME
CFLAGS	+= $(INCLUDES) $(DEFINES) 
CFLAGS	+= $(EXTRA)

DIRS	= errors utils vec tabset tabutils

all:

	for dir in $(DIRS); do $(MAKE) -C $$dir CFLAGS='$(CFLAGS)' ; done

clean:
	for dir in $(DIRS); do $(MAKE) -C $$dir $@; done

distclean: clean
	$(MAKE) -C tabutils $@
	
	

