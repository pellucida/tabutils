/*
//	@(#) errors.c
*/
# include	<errno.h>
# include	<stdio.h>
# include	<stdarg.h>
# include	<stdlib.h>
# include	<string.h>

# include	"bitfields/bitfields.h"
# include	"errors/errors.h"
# include	"utils/utils.h"

# include	"vec/vec_errors.h"
# include	"tabset/tabset_errors.h"
# include	"tabutils/tabutils_errors.h"

# define	TSIZE(x)	(sizeof(x)/sizeof(x[0]))

char	errors_no_error[]	= "No error";
char	errors_unknown_error[]	= "Unknown error";
char	errors_unknown_facility[]	= "Unknown facility";

errors_strerror_t*	errors_messages_table[]	= {
	[ERRORS_FACILITY_GLIBC]	= strerror,
	[ERRORS_FACILITY_VEC]	=	vec_errors_strerror,
	[ERRORS_FACILITY_TABSET]	=	tabset_errors_strerror,
	[ERRORS_FACILITY_TABUTILS]	=	tabutils_errors_strerror,
};

typedef	char*	errors_facility_t (void);
static	char*	glibc_errors_facility (void) {
	return	"glibc";
}
errors_facility_t*	errors_facility_table[]	= {
	[ERRORS_FACILITY_GLIBC]	= glibc_errors_facility,
	[ERRORS_FACILITY_VEC]	=	vec_errors_facility,
	[ERRORS_FACILITY_TABSET]	=	tabset_errors_facility,
	[ERRORS_FACILITY_TABUTILS]	=	tabutils_errors_facility,
};

char*	errors_strerror (result_t result) {
	char*	msg	= errors_unknown_facility;
	unsigned	facility	= ERRORS_FACILITY( result);
	if (facility < TSIZE(errors_messages_table)) {
		unsigned	erno	=	ERRORS_ERRNO( result);
		msg	= errors_messages_table [facility] (erno);
	}
	return	msg;
}
char*	errors_facility_name (result_t result) {
	unsigned	facility	= ERRORS_FACILITY( result);
	char*	name	= errors_unknown_facility;
	if (facility < TSIZE(errors_messages_table)) {
		name	= errors_facility_table [facility] ();
	}
	return	name;
}
void	fatal (char* fmt, ...) {
	va_list	ap;
	va_start (ap, fmt);
	fprintf (stderr, "ERROR: %s ", progname());
	vfprintf (stderr, fmt, ap);
	va_end (ap);
	exit (EXIT_FAILURE);
}
static	size_t	count_substr (char* ref, char* pat) {
	size_t	result	= 0;
	char*	t	= ref;
	char*	s	= strstr (t, pat);
	while (s) {
		++result;
		t	= s+1;
		s	= strstr (t, pat);
	}
	return	result;
}

static	void	fmt_subst (char* dest, size_t dlen, char* ref, int sc, char* msg) {
	char*	s	= ref;
	char*	end	= &dest[dlen];
	size_t	mlen	= strlen (msg);
	while (dest < end && *s != '\0') {
		int	ch	= *s;
		int	next	= s[1];
		if (ch == '%' && next  == sc){
			strcpy (dest, msg);
			dest	+= mlen;
			s	+= 2;
		}
		else	{
			*dest++	= *s++;
		}
		if (ch=='%' && next=='%') {
			*dest++	= *s++;
		}
	}
	*dest++	= '\n';
	*dest++	= '\0';
}
void	errors_fatal (result_t result, char* fmt, ...) {
	va_list	ap;
	char*	msg	= errors_strerror (result);
	size_t	mlen	= strlen (msg);
	size_t	count	= count_substr (fmt, "%m");
	size_t	buflen	= count*mlen + strlen(fmt)+1;
	char*	facility_name	= errors_facility_name (result);
	char	buf [buflen+1];
	fmt_subst (buf, buflen, fmt, 'm', msg);
	
	va_start (ap, fmt);
	
	fprintf (stderr, "ERROR: {%s} %s ", facility_name, progname());
	vfprintf (stderr, buf, ap);
	va_end (ap);
	exit (EXIT_FAILURE);
}
