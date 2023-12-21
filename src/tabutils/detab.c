/*
// @(#) detab.c
//
*/

# include	<unistd.h>
# include	<stdio.h>
# include	<stdint.h>
# include	<string.h>
# include	<stdlib.h>
# include	<stdarg.h>
# include	<stdint.h>
# include	<errno.h>

# include	"errors/errors.h"
# include	"vec/vec.h"
# include	"utils/utils.h"
# include	"tabset/tabset.h"


static	void	Usage (){
	char*	prog	= progname();
	fprintf (stderr, "Usage: %s [-T tab_repeat] [-t n,...] [file]\n", prog);
	fprintf (stderr, "\tThe default is %s -T 8\n", prog);
	fprintf (stderr, "\tTabs set at 3,6,9 then 14,21,... %s -t 3,6,9 -T 7\n", prog);
	exit (EXIT_FAILURE);
}

int	main (int argc, char* argv[]) {
	tabset_t*	tabset	= 0;
	result_t	result	= 0;
	int	opt	= EOF;
	char*	tabs	= 0;
	FILE*	input	= stdin;
	FILE*	output	= stdout;
	int	ch	= EOF;
	pos_t	p	= 0;	// position last printed
	char*	repeat	= 0;

# if    !defined( HAVE_PROGRAM_INVOCATION_SHORT_NAME)
	progname_set (argv[0], "detab");
# endif

	while ((opt = getopt (argc, argv, "ht:T:"))!=EOF) {
		switch (opt) {
		case	't':
			tabs	= optarg;
		break;
		case	'T':
			repeat	= optarg;
		break;
		case 	'h':
		default:
			Usage ();
		break;
		}
	}
	result	= tabset_Make (&tabset, tabs, repeat);
	if (result != ok) {
		errors_fatal (result, "tabset_Make(...,%s,%s) - [%m]", tabs, repeat);
	}
	if (optind+1 == argc) {
		char*	infile	= argv [optind];
		input	= fopen (infile, "r");
		if (input==0) {
			fatal ("cannot open '%s'\n", infile);
		}
	}
	while ((ch = fgetc (input)) != EOF) {
		if (ch == '\n') {
			fputc (ch, output);
			p	= 0;
		}
		else if (ch == '\t') {
			pos_t	tabpos	= tabset_next (tabset, p);
			if (p < tabpos) {
				spaces (output, tabpos-p);
				p	= tabpos;
			}
		}
		else {
			fputc (ch, output);
			++p;
		}
	}
	exit (EXIT_SUCCESS);
}
