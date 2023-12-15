/*
//	@(#)
*/

# include	"errors/errors.h"
# include	"tabutils/tabutils_errors.h"

# define	TSIZE(v)	(sizeof(v)/sizeof(v[0]))

# define	TABUTILS_FACILITY	"tabutils"

static  char*   tabutils_error_messages [] = {
        [ok]    = errors_no_error,
        [UNSUPP_TAB_REQ]        = "Unsupported tab processing requested",
};

char*	tabutils_errors_strerror (int erno){
	char*	result	= errors_unknown_error;
	if (erno >= 0 && erno < TSIZE(tabutils_error_messages)) {
		result	= tabutils_error_messages [erno];
	}
	return	result;
}
char*	tabutils_errors_facility (void){
	return	TABUTILS_FACILITY;
}
