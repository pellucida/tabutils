/*
//	@(#)
*/
# if	!defined(TABUTILS_ERRORS_H)
# define	TABUTILS_ERRORS_H

enum	{
	UNSUPP_TAB_REQ  = 1,
};
char*	tabutils_errors_strerror (int erno);
char*	tabutils_errors_facility (void);

# endif
