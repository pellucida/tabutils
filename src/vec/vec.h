/*
//	@(#) vec.h
*/
# if	!defined( VEC_H)
# define	VEC_H
//
// define elt_t on the compile command line eg -Delt_t="uint8_t"
//
# include	<stdlib.h>
# include	<stdint.h>

# include	"vec/vec_errors.h"

typedef	struct	vec_t	vec_t;
struct	vec_t	{
	size_t	size;
	size_t	used;
	elt_t*	vec;
};

static	inline	size_t	vec_used (vec_t* v){
	return	v->used;
}
static	inline	size_t	vec_size (vec_t* v){
	return	v->size;
}
static	inline	elt_t*	vec_vec (vec_t* v){
	return	v->vec;
}
result_t	vec_Create (vec_t** tsp, size_t size);
result_t	vec_grow (vec_t* ts, size_t size);
result_t	vec_Delete (vec_t** tsp);

// insert:
//   i>=used ==> error: NOT_INITIALIZED
//   vec [i>j>=0] == vec'[j] && vec [i] == pos && vec [used>=j>i] == vec'[j-1]
//   used == used' + 1

result_t	vec_insert (vec_t* ts, size_t i, elt_t pos);

// put:
//   i < used ==> error: AGAIN
//   vec [i] == pos && used == i + 1

result_t	vec_put (vec_t* ts, size_t i, elt_t pos);

// append: vec [used++]	== pos
static	inline	result_t	vec_append (vec_t* ts, elt_t pos) {
	return	vec_put (ts, vec_used (ts), pos);
}
// replace:
//  i>=used ==> error: NOT_INITIALIZED
//  vec [i] == pos
//  i >= used'	=> used == i + 1 [put(i,pos)]

static	inline	result_t	vec_replace (vec_t* ts, size_t i, elt_t pos){
	result_t        result  = ERRORS_VEC (NOT_INITIALIZED);
        
	if (i < ts->used) {
		ts->vec [i]     = pos;
		result  = ok;
	}
	return  result;
}
// clear:
//  i>=used ==> error: NOT_INITIALIZED
//  i < used => vec [i] == 0 

static	inline	result_t	vec_clear (vec_t* ts, size_t i) {
	return	vec_replace (ts, i, (elt_t)0);
}
// remove:
//  i>=used ==> error: NOT_INITIALIZED
//  vec [0<=j<i] == vec'[j] && vec [i<=j<used-1] == vec'[j+1]
//  used == used'-1

result_t	vec_remove (vec_t* ts, size_t i);

// get:
//  i>=used ==> error: NOT_INITIALIZED
//  pos == vec [i]

result_t	vec_get (vec_t* ts, size_t i, elt_t* pos);

# endif
