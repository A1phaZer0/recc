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
	unsigned mem;
	
	ap = arena[a];
	
	nbytes = roundup(nbytes, sizeof(union align));

	while (ap->avail + nbytes > ap->limit) {
		/* get a new block */
		if ((ap->next = freeblocks) != NULL) {
			freeblocks = freeblocks->next;
			ap = ap->next;
		} else {
			mem = sizeof(union header) + nbytes + 10 * 1024;
			ap->next = (struct block *)malloc(mem);
			ap = ap->next;
			if (ap == NULL) {
				printf("Insufficient memory!\n");
				exit(1);
			}
			ap->limit = (char *)ap + mem;
		}
		ap->avail = (char*)((union header *)ap + 1);
		ap->next = NULL;
		arena[a] = ap;
	}
	ap->avail += nbytes;
	return ap->avail - nbytes;
}

void *newarray(unsigned long m, unsigned long n, unsigned a)
{
	return allocate(m * n, a);
}

void deallocate(unsigned a)
{
	arena[a]->next = freeblocks;
	freeblocks = first[a].next;
	first[a].next = NULL;
	arena[a] = &first[a];
}
