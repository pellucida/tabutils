/*
//	@(#)
*/
# if	!defined(TABSET_ERRORS_H)
# define	TABSET_ERRORS_H

enum	{
	NOT_ASCENDING   = 1,
	NOT_POSITIVE    = 2,
	NUMBER_TOO_BIG  = 3,
};

char*	tabset_errors_strerror (int erno);
char*	tabset_errors_facility (void);
# endif
