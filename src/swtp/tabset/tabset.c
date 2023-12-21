/*
// @(#) tabset.c
*/

# include	<stdio.h>
# include	<stdint.h>
# include	<string.h>
# include	<stdlib.h>
# include	<stdarg.h>
# include	<stdint.h>
# include	<errno.h>

# include	"utils/utils.h"
# include	"errors/errors.h"
# include	"mem/new.h"
# include	"vec/vec.h"
# include	"tabset/tabset.h"
# include	"tabset/tabset_errors.h"

result_t	tabset_Create (tabset_t** tsp, vec_t* shifts, pos_t repeat) {
	tabset_t*	ts	= 0;
	result_t	result	= New (ts);
	if (result==ok) {
		*ts	= (typeof(*ts)){
			.repeat	= repeat,
			.shifts	= shifts,
		};
		*tsp	= ts;
		result	= ok;
	}
	return	result;
}
pos_t	tabs_repeat (pos_t pos, pos_t repeat) {
	pos_t	result	= ((pos/repeat)+1)*repeat;
	return	result;
}
	
pos_t	tabset_next (tabset_t* ts, pos_t pos) {
	pos_t	nextpos	= 0;
	pos_t	maxshift	= (ts->shifts)?vec_used (ts->shifts):0;
	if (pos < maxshift) {
		delta_t	delta	= 0;
		result_t	result	= vec_get (ts->shifts, pos, &delta);
		if (result==ok) {
			nextpos	= pos + delta;
		}
		else	{
			errors_fatal (result, "vec_get (..., %u, &delta) - [%m]", pos);
		}
	}
	else	{
		nextpos	= tabs_repeat (pos, ts->repeat);
	}
	return	nextpos;
}

static	inline	result_t	get_number (pos_t* pos, char* str, char** nextp){
	unsigned long	p	= 0;
	result_t	result	= get_positive (&p, str, nextp);
	if (result==ok) {
		if (p < UINT16_MAX) {
			*pos	= p;
		}
		else	{
			result	= ERRORS_TABSET (NUMBER_TOO_BIG);
		}

	}
	else	{
		result	= ERRORS_TABSET (NUMBER_TOO_BIG);
	}
	return	result;
}

// -t tabs -- tabs : num | tabs ',' num
enum	{
	TABLIST_SEP	= ',',
};
result_t	tabs_parse (vec_t* shifts, char* tabstr) {
	result_t	result	= ok;
	char*	tabs	= tabstr;
	pos_t	previous	= 0;
	while (tabs) {
		char*	next	= 0;
		pos_t	pos	= 0; 
		result	= get_number (&pos, tabs, &next);
		if (result!=ok) {
			tabs	= 0;
		}
		else if (previous >= pos) {
			result	= ERRORS_TABSET (NOT_ASCENDING);
			tabs	= 0;
		}
		else {
			size_t	i	= previous;
			for (i=previous; i < pos && result==ok; ++i) {
				pos_t	delta	= (pos - i);
				if (delta <= UINT8_MAX) {
					result	= vec_put (shifts, i, (delta_t)delta);
				}
				else	{
					result	= ERRORS_TABSET (NUMBER_TOO_BIG);
					tabs	= 0;
				}
			}
			if (result != ok || *next == '\0') {
				tabs	= 0;
			}
			else if (*next == TABLIST_SEP) {
				tabs	= next+1;
				previous	= pos;
			}
			else {
				tabs	= 0;
				result	= ERRORS_TABSET (NOT_POSITIVE);
			}
		}
	}
	return	result;
}
result_t	tabset_Make (tabset_t** tsp, char* tabstr, char* repeatstr) {
	tabset_t*	ts	= 0;
	pos_t	repeat	= TAB_REPEAT;
	vec_t*	shifts	= 0;
	result_t	result	= vec_Create (&shifts, 0);
	
	if (result!=ok) {
		errors_fatal (result, "vec_Create (&shifts, default) - [%m]");
	}
	if (tabstr) {
		result	= tabs_parse (shifts, tabstr);
	}
	if (result != ok) {
		errors_fatal (result, "-t %s - tabs_parse (shifts, %s) - [%m]", tabstr, tabstr);
	}
	if (repeatstr) {
		result	= get_number (&repeat, repeatstr, 0);
	}
	if (result != ok) {
		errors_fatal (result, "-T %s - [%m]", repeatstr);
		//fatal_error ("-T <n>", result);
	}
	result	= tabset_Create (&ts, shifts, repeat);
	if (result == ok) {
		*tsp	= ts;
	}
	return	result;
}
