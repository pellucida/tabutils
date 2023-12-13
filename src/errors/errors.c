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

# define	TSIZE(x)	(sizeof(x)/sizeof(x[0]))

// Application supplied message list - for _strerror()

extern	error_messages_t	vec_messages;
extern	error_messages_t        tabset_messages;
extern	error_messages_t        tabutils_messages;

// Table of message lists indexed by facility

error_messages_t*	error_messages_tab[]	= {
	[ERRORS_FACILITY_GLIBC]	=	0,
	[ERRORS_FACILITY_VEC]	=	&vec_messages,
	[ERRORS_FACILITY_TABSET]	=	&tabset_messages,
	[ERRORS_FACILITY_TABUTILS]	=	&tabutils_messages,
};

error_messages_table_t	error_messages_tables	= {
	.n_tables	= TSIZE(error_messages_tab),
	.messages	= error_messages_tab,
};

static	result_t	errors_facility_messages (error_messages_t** fmpp, unsigned facility) {
	result_t	retval	= err;
	if (facility < error_messages_tables.n_tables) {
		error_messages_t**	messages	= error_messages_tables.messages;
		error_messages_t*	fmsg	= messages [facility];
		*fmpp	= fmsg;
		retval	= ok;
	}
	return	retval;
}

char*	errors_strerror (result_t result) {
	char*	msg	= "Unknown facility";
	unsigned	facility	= ERRORS_FACILITY( result);
	unsigned	erno	=	ERRORS_ERRNO( result);
	if (facility==ERRORS_FACILITY_GLIBC) {
		msg	= strerror (erno);
	}
	else	{
		error_messages_t*	errmsg	= 0;
		result_t	rv	= errors_facility_messages (&errmsg, facility);
		if (rv==ok) {
			if (erno < errmsg->n_messages) {
				msg	= errmsg->messages[erno];
			}
			else	{
				msg	= "Unknown error";
			}
		}
	}
	return	msg;
}
char*	errors_facility_name (result_t result) {
	unsigned	facility	= ERRORS_FACILITY( result);
	char*	name	= "GLIBC";
	if (facility != ERRORS_FACILITY_GLIBC){
		error_messages_t*	errmsg	= 0;
		result_t	rv	= errors_facility_messages (&errmsg, facility);
		if (rv==ok) {
			name	= errmsg->facility_name;
		}
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
