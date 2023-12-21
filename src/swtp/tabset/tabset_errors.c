/*
//	@(#)
*/

# include	"errors/errors.h"
# include	"tabset/tabset_errors.h"

# define	TSIZE(v)	(sizeof(v)/sizeof(v[0]))

# define	TABSET_FACILITY	"tabset"

static  char*   tabset_error_messages [] = {
        [ok]    = errors_no_error,
        [NOT_ASCENDING] = "Tab position must be strictly ascending",
        [NOT_POSITIVE]  = "Positive number expected",
        [NUMBER_TOO_BIG]        = "Tab stop too far from previous stop", 
};

char*	tabset_errors_strerror (int erno){
	char*	result	= errors_unknown_error;
	if (erno >= 0 && erno < TSIZE(tabset_error_messages)) {
		result	= tabset_error_messages [erno];
	}
	return	result;
}
char*	tabset_errors_facility (void) {
	return	TABSET_FACILITY;
}
