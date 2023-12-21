/*
// @(#) tabset.h
*/
# if	!defined( TABSET_H)
# define	TABSET_H

# include	"errors/errors.h"
# include	"vec/vec.h"

enum { TAB_REPEAT      = 8, };

typedef	uint16_t 	pos_t;
typedef	elt_t	delta_t;
typedef	struct	tabset_t	tabset_t;
struct	tabset_t {
	vec_t*  stops;
	pos_t   repeat;
//
//	cache
//
	/*const*/	pos_t	first;
	/*const*/	pos_t	last;
	size_t	prior;
};


result_t	tabset_Create (tabset_t** tsp, vec_t* shifts, pos_t repeat);
pos_t	tabs_repeat (pos_t pos, pos_t repeat);
pos_t	tabset_next (tabset_t* ts, pos_t pos);
result_t	tabs_parse (vec_t* shifts, char* tabstr);
result_t	tabset_Make (tabset_t** tsp, char* tabstr, char* repeatstr);

# endif
