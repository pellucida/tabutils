/*
//	@(#)
*/

# include	"errors/errors.h"
# include	"tabset/tabset_errors.h"

# define	TSIZE(v)	(sizeof(v)/sizeof(v[0]))

static  char*   tabset_error_messages [] = {
        [ok]    = "No error",
        [NOT_ASCENDING] = "Tab position must be strictly ascending",
        [NOT_POSITIVE]  = "Positive number expected",
        [NUMBER_TOO_BIG]        = "Tab stop too far from previous stop", 
        [UNSUPP_TAB_REQ]        = "Unsupported tab processing requested",
};
error_messages_t        tabset_messages    = (error_messages_t){
        .n_messages     = TSIZE(tabset_error_messages),
        .facility_name  = "tabset",
        .messages       = tabset_error_messages,
};

