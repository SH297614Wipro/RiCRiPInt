#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <unistd.h>

#define RIPSIZ ((8 * 1024 * 1024))
struct memblk {
    struct memblk *next;
    long  msize;
    char addr[0];
};

typedef struct memblk* BLK;
extern char *ripAddr;
int meminit();
void *mmalloc(int count);
void mdefrag(void);
void mfree(void *r);
