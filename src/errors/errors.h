/*
//	@(#) errors.h
*/
# if	!defined( ERRORS_H)
# define	ERRORS_H
# include	<errno.h>
# include	<string.h>
# include	<stdint.h>

# include	"bitfields/bitfields.h"

typedef	uint32_t	result_t;

enum	{
	ok	= 0,
	err	= (result_t)(-1),
};

//
// result_t	err:1,unused:7,facility:8,errno:16
//
enum	{
	ERRORS_SHIFT_ERRNO	= 0,
	ERRORS_WIDTH_ERRNO	= 16,
	ERRORS_SHIFT_FACILITY	= ERRORS_SHIFT_ERRNO+ERRORS_WIDTH_ERRNO,
	ERRORS_WIDTH_FACILITY	= 8,
	ERRORS_SHIFT_UNUSED	= ERRORS_SHIFT_FACILITY+ERRORS_WIDTH_FACILITY,
	ERRORS_WIDTH_UNUSED	= 7,
	ERRORS_SHIFT_ERR		= ERRORS_SHIFT_UNUSED+ERRORS_WIDTH_UNUSED, 
	ERRORS_WIDTH_ERR		= 1,
};
enum	{
	ERRORS_FACILITY_GLIBC	= 0,
	ERRORS_FACILITY_VEC	= 1,
	ERRORS_FACILITY_TABSET	= 2,
	ERRORS_FACILITY_TABUTILS	= 3,
};

# define	ERRORS_MASK_ERR		(BF32_MASK_FLD(ERRORS_WIDTH_ERR, ERRORS_SHIFT_ERR))
# define	ERRORS_MASK_FACILITY	(BF32_MASK_FLD(ERRORS_WIDTH_FACILITY, ERRORS_SHIFT_FACILITY))
# define	ERRORS_MASK_ERRNO	(BF32_MASK_FLD(ERRORS_WIDTH_ERRNO, ERRORS_SHIFT_ERNNO))


# define	ERRORS_ENCODE( facility, code)	(BF32_SETFLD((facility),ERRORS_WIDTH_FACILITY,ERRORS_SHIFT_FACILITY)|\
			BF32_SETFLD((code),ERRORS_WIDTH_ERRNO,ERRORS_SHIFT_ERRNO)|ERRORS_MASK_ERR)	

# define	ERRORS_ERR(result)	(BF32_GETFLD((result),ERRORS_WIDTH_ERR,ERRORS_SHIFT_ERR))
# define	ERRORS_FACILITY(result)	(BF32_GETFLD((result),ERRORS_WIDTH_FACILITY,ERRORS_SHIFT_FACILITY))
# define	ERRORS_ERRNO(result)	(BF32_GETFLD((result),ERRORS_WIDTH_ERRNO,ERRORS_SHIFT_ERRNO))

# define	ERRORS_GLIBC( code)	ERRORS_ENCODE( ERRORS_FACILITY_GLIBC, code)
# define	ERRORS_VEC( code)	ERRORS_ENCODE( ERRORS_FACILITY_VEC, code)
# define	ERRORS_TABSET( code)	ERRORS_ENCODE( ERRORS_FACILITY_TABSET, code)
# define	ERRORS_TABUTILS( code)	ERRORS_ENCODE( ERRORS_FACILITY_TABUTILS, code)

struct	error_messages_t	{
	size_t	n_messages;
	char*	facility_name;
	char**	messages;
};
typedef	struct	error_messages_t	error_messages_t;

struct	error_messages_table_t	{
	size_t	n_tables;
	error_messages_t**	messages;
};
typedef	struct	error_messages_table_t	error_messages_table_t;

char*	errors_strerror (result_t result);
void	fatal (char* fmt, ...);
void	errors_fatal (result_t result, char* fmt, ...);
char*	errors_facility_name (result_t result);

# endif
