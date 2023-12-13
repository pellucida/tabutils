/*
// @(#) bitfieds.h - portably? manipulate bit fields 
*/
# if	!defined( BITFIELDS_H)
# define	BITFIELDS_H

# include	<stdint.h>
//
// _clrbits(w)  - mask to zero last w bits, preserve the first N-w bits
// _bits(w) 	- mask off the last w bits
// _mask_fld(w,n)	- mask off bits n to n+w
// _mask_clrfld(w,n)	- mask to clear bits n to n+w
// _setfld(x,w,n)	- shift and mask x to set bits n..n+w (OR)	
// _clrfld(x,w,n)	- shift and mask x clear bits n..n+w (AND)
// _getfld(x,w,n)	- shift bits n..n+w, n position to left and mask 
//
# define	BF32_CLRBITS(width)	((~(uint32_t)(0))<<(width))	
# define	BF32_BITS(width)	(~(BF32_CLRBITS(width)))	
# define	BF32_MASK_FLD(width,off)	(((uint32_t)(BF32_BITS(width)))<<(off))
# define	BF32_MASK_CLRFLD(width,off)	(~BF_MASK_FLD(width,off))
# define	BF32_SETFLD(x,width,off)	(((uint32_t)(x) & BF32_BITS(width))<<(off))
# define	BF32_CLRFLD(x,width,off)	((uint32_t)(x) & BF32_MASK_CLRFLD(width,off))
# define	BF32_GETFLD(x,width,off)	(((uint32_t)(x)>>(off))&BF32_BITS(width))

# define	BF64_CLRBITS(width)	((~(uint64_t)(0))<<(width))	
# define	BF64_BITS(width)	(~(BF64_CLRBITS(width)))	
# define	BF64_MASK_FLD(width,off)	(((uint64_t)(BF64_BITS(width)))<<(off))
# define	BF64_MASK_CLRFLD(width,off)	(~BF_MASK_FLD(width,off))
# define	BF64_SETFLD(x,width,off)	(((uint64_t)(x) & BF64_BITS(width))<<(off))
# define	BF64_CLRFLD(x,width,off)	((uint64_t)(x) & BF64_MASK_CLRFLD(width,off))
# define	BF64_GETFLD(x,width,off)	((uint64_t)(x)>>(off)&BF64_BITS(width))

# define	BF16_CLRBITS(width)	((~(uint16_t)(0))<<(width))	
# define	BF16_BITS(width)	(~(BF16_CLRBITS(width)))	
# define	BF16_MASK_FLD(width,off)	(((uint16_t)(BF16_BITS(width)))<<(off))
# define	BF16_MASK_CLRFLD(width,off)	(~BF_MASK_FLD(width,off))
# define	BF16_SETFLD(x,width,off)	(((uint16_t)(x) & BF16_BITS(width))<<(off))
# define	BF16_CLRFLD(x,width,off)	((uint16_t)(x) & BF16_MASK_CLRFLD(width,off))
# define	BF16_GETFLD(x,width,off)	((uint16_t)(x)>>(off)&BF16_BITS(width))

# endif
