/*
// @(#) utils.h
*/
# if	!defined( UTILS_H)
# define	UTILS_H

# include	<stdio.h>
# include	<stdarg.h>

# include	"errors/errors.h"

void	spaces (FILE* output, size_t n);
result_t	get_positive (unsigned long* tp, char* str, char** nextp);

// Glibc has basename in <string.h>
# if	!defined( HAVE_BASENAME)
char*	basename (char* s);
# endif


# if	!defined( HAVE_PROGRAM_INVOCATION_SHORT_NAME)
enum	{
	PROGNAME_GET	= 0,
	PROGNAME_SET	= 1,
};
//
char*	progname_util (int what, char* argv0, char* fallback);
static	inline	char*	progname () {
	return	progname_util (PROGNAME_GET, 0, 0);
}
static	inline	char*	progname_set (char* argv0, char* fallback) {
	return	progname_util (PROGNAME_SET, argv0, fallback);
}
# else
static  inline  char*   progname () {
        return  program_invocation_short_name;
}
static	inline	char*   progname_set (char* argv0, char* fallback) {
	return	program_invocation_short_name;
}
# endif
# endif
