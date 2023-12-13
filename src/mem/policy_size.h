/*
//	@(#) policy_size.h
*/
# if	!defined( POLICY_SIZE_H)
# define	POLICY_SIZE_H

# include	<stdlib.h>

// Actually just ensures at least SIZE_MIN allocation
// OR round up to SIZE_STEP boundary
// Probably thinking
//  [((size-SIZE_MIN)+(SIZE_STEP-1))/SIZE_STEP]*SIZE_STEP + SIZE_MIN

enum	{
	MEM_SIZE_MIN	= 64,
	MEM_SIZE_STEP	= 64,
};
static	inline	size_t	policy_size (size_t size) {
	size_t	result	= MEM_SIZE_MIN;
	if (size > result) {
		result	= ((size + (MEM_SIZE_STEP - 1))/MEM_SIZE_STEP)*MEM_SIZE_STEP;
	}
	return	result;
}
# endif
