/*
//	@(#)
*/

# include	"errors/errors.h"
# include	"tabutils/tabutils_errors.h"

# define	TSIZE(v)	(sizeof(v)/sizeof(v[0]))

static  char*   tabutils_error_messages [] = {
        [ok]    = "No error",
        [UNSUPP_TAB_REQ]        = "Unsupported tab processing requested",
};
error_messages_t        tabutils_messages    = (error_messages_t){
        .n_messages     = TSIZE(tabutils_error_messages),
        .facility_name  = "tabutils",
        .messages       = tabutils_error_messages,
};

