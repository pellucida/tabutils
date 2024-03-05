/*
// @(#) vec.c
//
*/

# include	<errno.h>
# include	<stdlib.h>

# include	"errors/errors.h"
# include	"mem/new.h"
# include	"mem/policy_size.h"
# include	"vec/vec.h"
# include	"vec/vec_errors.h"

// Note: only _append() and _put() place values after [used-1]
// _put(i,x) initializes vec[used..i-1] before setting vec[i]==x

result_t	vec_grow (vec_t* ts, size_t size) {
	result_t	result	= ok;
	if (size == 0 || size > ts->size) {
		size_t	newsize	= policy_size (size);
		result	= Resize_Vec (ts->vec, newsize);
		if (result==ok) {
			// No init. of vec[used..newsize-1] is required
			ts->size	= newsize;
		}
		else	{
			result	= ERRORS_GLIBC (ENOMEM);
		}
	}
	return	result;
}

result_t	vec_Create (vec_t** tsp, size_t size) {
	vec_t*	ts	= 0;
	result_t	result	= New (ts);
	if (result==ok) {
		*ts	= (typeof(*ts)){
			.size	= 0,
			.used	= 0,
			.vec	= 0,
			};
		result	= vec_grow (ts, size);
		if (result == ok) {
			*tsp	= ts;
		}
		else	{
			free (ts);
		}
	}
	return	result;
}
result_t	vec_Delete (vec_t** tsp) {
	if (tsp && *tsp) {
		vec_t*	ts	= *tsp;
		if (ts->vec) {
			free (ts->vec);
		}
		free (ts);
		*tsp	= 0;
	}
	return	ok;
}
result_t	vec_get (vec_t* ts, size_t i, elt_t* x) {
	result_t	result	= ERRORS_VEC (NOT_INITIALIZED);
	if (i < ts->used) {
		*x	= ts->vec [i];
		result	= ok;
	}
	return	result;
}
result_t	vec_put (vec_t* ts, size_t i, elt_t x) {
	result_t	result	= ok;
	size_t	used	= ts->used;
	if (i >= used) {
		if (i >= ts->size) {
			result	= vec_grow (ts, i+1);
		}
		if (result==ok) {
			typeof(ts->vec)	vec	= ts->vec;
			size_t	j	= used;
			for (; j < i; ++j) {
				vec [j]	= 0;
			}
			vec [i]	= x;
			ts->used	= i+1;
		}
	}
	else	result	= ERRORS_VEC (WOULD_OVERWRITE);
	return	result;
}
result_t	vec_remove (vec_t* ts, size_t i){
	result_t	result	= ERRORS_VEC (NOT_INITIALIZED);
	
	size_t	used	= ts->used;
	if (i < used) {
		typeof(ts->vec)	vec	= ts->vec;
		size_t	j	= i+1;
		for (; j < used; ++j) { 
			vec [j-1]	= vec [j];
		}
		vec [used-1]	= 0;
		ts->used--;
		result	= ok;
	}
	return	result;
}
result_t	vec_insert (vec_t* ts, size_t i, elt_t x) {
	result_t	result	= ERRORS_VEC (NOT_INITIALIZED);
	
	size_t	used	= ts->used;
	if (i < used) {
		if (used >= ts->size) {
			result	= vec_grow (ts, used+1);
		}
		if (result==ok) {
			typeof(ts->vec)	vec	= ts->vec;
			size_t	j	= used;
			for (; j > i; --j) {
				vec [j]	= vec [j-1];
			}
			vec [i]	= x;
			ts->used++;
			result	= ok;
		}
	}
	return	result;
}
