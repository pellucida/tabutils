/*
//	@(#)
*/
# include	"errors/errors.h"
# include	"vec/vec_errors.h"

# define	TSIZE(v)	(sizeof(v)/sizeof(v[0]))

static  char*   vec_error_messages []   = {
        [ok]    = "No error",
        [NOT_INITIALIZED]       = "Access outside range",
        [WOULD_OVERWRITE]       = "Cannot put() into existing location. Use replace()",
};

error_messages_t        vec_messages    = (error_messages_t){
	.n_messages     = TSIZE(vec_error_messages),
	.facility_name	= "vec",
	.messages       = vec_error_messages,
};

