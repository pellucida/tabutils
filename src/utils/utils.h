/*
// @(#) utils.h
*/
# if	!defined( UTILS_H)
# define	UTILS_H

# include	<stdio.h>
# include	<stdarg.h>

# include	"errors/errors.h"

void	spaces (FILE* output, size_t n);
char*	basename (char* s);
result_t	get_positive (unsigned long* tp, char* str, char** nextp);

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

# endif
