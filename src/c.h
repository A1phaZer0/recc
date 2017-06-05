#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>


/* round up to the least multiple of n that is not
 * lesser than x */
#define roundup(x,n) (((x)+((n)-1))&(~((n)-1)))

#define NELEMS(a) ((int)(sizeof (a)/sizeof ((a)[0)))
