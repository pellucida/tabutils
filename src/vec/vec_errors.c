/*
//	@(#)
*/
# include	"errors/errors.h"
# include	"vec/vec_errors.h"

# define	TSIZE(v)	(sizeof(v)/sizeof(v[0]))

# define	VEC_FACILITY	"vec"

static  char*   vec_error_messages []   = {
        [ok]    = errors_no_error,
        [NOT_INITIALIZED]       = "Access outside range",
        [WOULD_OVERWRITE]       = "Cannot put() into existing location. Use replace()",
};

char*	vec_errors_strerror (int erno) {
	char*	result	= errors_unknown_error;
	if (erno >= 0 && erno < TSIZE(vec_error_messages)){
		result	= vec_error_messages [erno];
	}
	return	result;
}
char*	vec_errors_facility (void){
	return	VEC_FACILITY;
}
