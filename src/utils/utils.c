/*
// @(#) utils.c
*/

# include	<stdio.h>
# include	<string.h>

# include	"errors/errors.h"
# include	"utils/utils.h"

void	spaces (FILE* output, size_t n){
	int	i	= 0;
	for (i=0; i < n; ++i) {
		fputc (' ', output);
	}
}
# if	!defined( HAVE_BASENAME)
char*	basename (char* s) {
	char*	result	= s;
	char*	t	= strrchr (s, '/');
	if (t) {
		result	= t+1;
	}
	return	result;
}
# endif

# if	!defined( HAVE_PROGRAM_INVOCATION_SHORT_NAME)
char*	progname_util (int what, char* argv0, char* fallback) {
	static	char*	progname	= 0; 
	char*	result	= progname;
	if (what == PROGNAME_SET) {
		if (argv0) {
			progname	= basename (argv0);
		}
		else	{
			progname	= fallback;
		}
	}
	return	result;
}
# endif
// --------------------------------------------------
// convert 'str' to into positive number [0..n]]
//
result_t	get_positive (unsigned long* tp, char* str, char** nextp) {
	result_t	result	= ERRORS_GLIBC (ERANGE);
	char*	tend	= 0;
	typeof(*tp)	t	= strtoul (str, &tend, 10);
	if (str < tend){
		*tp	= t;
		result	= ok;
	}
	if (nextp) {
		*nextp	= tend;
	}
	return	result;
}
