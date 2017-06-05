#include "c.h"

struct block {
	struct block *next;
	char *avail;
	char *limit;
};

union align {
	long l;
	char *p;
	double d;
	int (*f)(void);
};

/* make sure every header of allocation zone has
 * rightful alignment. */
union header {
	struct block b;
	union align a;
};

static struct block first[3] = {{NULL,}, {NULL,}, {NULL,}};
static struct block *arena[3] = {&first[0], &first[1], &first[2]};
static struct block *freeblocks;

void *allocate(unsigned long nbytes, unsigned a)
{
	struct block *ap;
	
	ap = arena[a];
	
	nbytes = roundup(nbytes, sizeof(union align));

	if (ap->avail + nbytes > ap->limit) {
		/* get a new block */
	}
	ap->avail += nbytes;
	return ap->avail - nbytes;
}
