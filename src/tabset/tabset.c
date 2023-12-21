/*
// @(#) tabset.c
*/

# include	<stdio.h>
# include	<stdint.h>
# include	<string.h>
# include	<stdlib.h>
# include	<stdarg.h>
# include	<stdint.h>
# include	<stdbool.h>
# include	<errno.h>

# include	"utils/utils.h"
# include	"errors/errors.h"
# include	"mem/new.h"
# include	"vec/vec.h"
# include	"tabset/tabset.h"
# include	"tabset/tabset_errors.h"

// Various levels of safety in _get() from vec_t* 
// vec_append() is too complicated and isn't used enough to bother.

# if !defined (VEC_DIRECT)
static	inline	pos_t	vec_at (vec_t* v, size_t i) {
	pos_t	result	= 0;
	result_t	rv	= vec_get (v, i, &result);
	if (rv!=ok){
		errors_fatal (rv, "vec_get (..., %u, &result) - [%m]", i);
	}
	return	result;
}
# else
#	if !defined( VEC_UNSAFE)
# include	"vec/vec_errors.h"
static	inline	pos_t	vec_at (vec_t* v, size_t i) {
	if (i >= v->used) {
		errors_fatal (ERRORS_VEC (NOT_INITIALIZED), "vec_at (..., %u) - [%m]", i);
	}
	return	v->vec [i];
}
# 	else
static	inline	pos_t	vec_at (vec_t* v, size_t i) {
	return	v->vec [i];
}
#	endif
# endif

result_t	tabset_Create (tabset_t** tsp, vec_t* stops, pos_t repeat) {
	tabset_t*	ts	= 0;
	result_t	result	= New (ts);
	if (result==ok) {
		pos_t	first	= 0;
		pos_t	last	= 0;
		if (vec_used (stops) != 0) {
			first	= vec_at (stops, 0);
			last	= vec_at (stops, vec_used(stops)-1);
		}
		*ts	= (typeof(*ts)){
			.repeat	= repeat,
			.stops	= stops,
			.first	= first,
			.last	= last,
			.prior	= 0,
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

// Locate largest t: stops[i] < pos <= stops[t] <= stops [j]

// Pre: 0 <= i < j < used and stops [i] < pos <= stops [j] 

static	size_t	vec_locate (vec_t* stops, size_t i, size_t j, pos_t pos) {

// INV:	stops[i] < pos <= stops[j] and j > i

	while (j > i+1) { // j-i > 1 ; m-i >= (j-i)/2 >= 1
			  // j-m >= (j-i)/2 >= 1

		size_t	m	= (j+i+1)/2; // m >= i+1, j >= m+1 
		pos_t	tm	= vec_at (stops, m);
		if (pos <= tm) {
			j	= m;	// stops[i] < pos <= stops[m]
				 	// m >= i+1 => j>=i+1 
		}
		else /* pos > tm */ {	// stops[m] < pos <= stops[j]
			i	= m;	// j >= m+1 => j>=i+1
		}
// pos <= stops[m] =>
//	wp("j := m", stops[i]<pos<=stops[j]) = stops[i]<pos<=stops[m]
// pos > stops[m] =>
//	wp("i := m", stops[i]<pos<=stops[j]) = stops[m]<pos<=stops[j]
// ==>  INV
	}
// G: j <= i+1 and INV: j > i ==> j == i+1 
// INV: stops[i] < pos <= stops[j] ==> stops[i] < pos <= stops [i+1]
// 
	return	j;	// == i+1
}

pos_t	tabset_next (tabset_t* ts, pos_t pos) {
	result_t	result	= ok;
	pos_t	nextpos	= 0;
	vec_t*	stops	= ts->stops;
	size_t	used	= vec_used (stops);
	pos_t	first	= ts->first;
	pos_t	last	= ts->last;
	size_t	prior	= ts->prior;

// First test the common edge cases
//  1. No enumerated tabs or beyond last enumerated tab position
	if (used==0 || pos > last) {
		prior	= 0;
		nextpos	= tabs_repeat (pos, ts->repeat);
	} // else used>0 and pos <= last
//  2. At the start of the line
	else if (pos <= first) {
		prior	= 0;
		nextpos	= first;
	} // else pos > first and used>0 and pos <= last ==> first!=last ==> used>1
// 
	else {	

// At this point we have
// 	pos > first and used>1 and pos <= last
//	stops[0] < pos <= stops[used-1]
//
// We have cached first =def stops[0], last =def stops[used-1]
// and prior caches the previous tab stop returned 
// prior is valid if pos > stops [prior] else start from 0
// If prior is valid check whether stops[prior+1] is the next stop
// ie stops [prior] < pos <= stops[prior+1]
// If so we are done
// Otherwise if pos > stops[prior+1] we can search [prior+1..used-1]
// Else search [0..used-1]

		size_t	i	= 0;
		size_t	j	= used-1;
		bool	found	= false;
		pos_t	prival	= vec_at (stops, prior);

		if (prival < pos) { // stops[prior] < pos
			pos_t	nextval	= vec_at (stops, prior+1);
			i	= prior; // We can start search here 

			if (pos <= nextval) { // found next tab stop
				prior	= prior + 1;	
				nextpos	= nextval;
				found	= true;
			}
			else { // pos > nextval (stops[prior+1])
				i	= prior + 1;
			}
		}
		if (!found) { // binary search
			//	stops[i] < pos <= stops[j], used > j >= i >=0
			j	= vec_locate (stops, i, j, pos);
			nextpos	= vec_at (stops, j);
			prior	= j;
		}
	}
	ts->prior	= prior;
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
result_t	tabs_parse (vec_t* stops, char* tabstr) {
	result_t	result	= ok;
	char*	tabs	= tabstr;
	pos_t	previous	= 0;
	while (tabs) {
		char*	next	= 0;
		pos_t	pos	= 0; 
		result	= get_number (&pos, tabs, &next);
		if (result!=ok) {
			result	= ERRORS_TABSET (NOT_POSITIVE);
			tabs	= 0;
		}
		else if (previous >= pos) {
			result	= ERRORS_TABSET (NOT_ASCENDING);
			tabs	= 0;
		}
		else {
			result	= vec_append (stops, pos);
			if (result != ok || *next == '\0') {
				tabs	= 0;
			}
			else if (*next == TABLIST_SEP) {
				tabs	= next+1;
				previous	= pos;
			}
		}
	}
	return	result;
}
result_t	tabset_Make (tabset_t** tsp, char* tabstr, char* repeatstr) {
	tabset_t*	ts	= 0;
	pos_t	repeat	= TAB_REPEAT;
	vec_t*	stops	= 0;

	result_t	result	= vec_Create (&stops, 0);
	
	if (result!=ok) {
		errors_fatal (result, "vec_Create (&stops, default) - [%m]");
	}
	if (tabstr) {
		result	= tabs_parse (stops, tabstr);
		if (result != ok) {
			errors_fatal (result, "-t %s - tabs_parse (stops, %s) - [%m]", tabstr, tabstr);
		}
	}
	if (repeatstr) {
		result	= get_number (&repeat, repeatstr, 0);
	}
	if (result != ok) {
		errors_fatal (result, "-T %s - [%m]", repeatstr);
	}
	result	= tabset_Create (&ts, stops, repeat);
	if (result == ok) {
		*tsp	= ts;
	}
	return	result;
}
