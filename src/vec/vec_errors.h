/*
//	@(#)
*/
# if	!defined(VEC_ERRORS_H)
# define	VEC_ERRORS_H

enum	{
	NOT_INITIALIZED = 1, 
	WOULD_OVERWRITE = 2, 
};
char*	vec_errors_strerror (int erno);
char*	vec_errors_facility (void);

# endif
