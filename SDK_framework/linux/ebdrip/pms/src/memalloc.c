#include "memalloc.h"

#define RIPSIZ ((8 * 1024 * 1024))
BLK FL = NULL;
BLK AL = NULL; 
static long memcount=0;
static long maxmem = 0;
char *ripAddr = NULL;
extern caddr_t memaddr;
extern long szFreeBytes;
int minit()
{
    FL = (BLK) memaddr;
    if(FL!=NULL)
    {
        FL->next =  NULL;
        FL->msize = szFreeBytes - sizeof(struct memblk);
    }
    else
    {
        printf(" malloc failed \n");
        exit(1);
    }
}

void *mmalloc(int size)
{
    
    if(!FL)
    {
	minit();
    }

    BLK q, p, newfreepacket, nextfreepacket;
    int mreq =  size + sizeof(struct memblk);
    if(size <= 0)
    {
        return NULL;
    }
    q = p = FL;
    while((p->msize < mreq) && p->next)
    {
        q = p;
        p = p->next;
    }
    if( p->msize >=  mreq )
    {
        nextfreepacket = p->next;
        if(p->msize > mreq)
        {

            newfreepacket = (BLK) &(p->addr[size]);
            newfreepacket->msize = p->msize - mreq;
            newfreepacket->next = nextfreepacket;

            if( p == q )
            {
                FL =  newfreepacket;
            }
            else
            {
                q->next =  newfreepacket;
            }
        }
        else
        {

            if( p ==  q )
            {
                FL = nextfreepacket;
            }
            else
            {
                q->next = nextfreepacket;
            }
        }

        p->msize = size;
	memcount+=size;
	if(maxmem < memcount)
	{
		maxmem = memcount;
		printf("outside core memory usage = %d\n", maxmem);
	}
        if( AL )
        {
            p->next = AL;
            AL = p;
        }
        else
        {
            AL = p;
        }
	if(size > RIPSIZ)
        	ripAddr=p->addr;
        
	return p->addr;
    }
    else
    {
        return NULL;
    }
}

void coalesce(void)
{

    BLK p, q, cur;
    p = FL;
    while(p)
    {
        q = p;
        p = p->next;
        if(p)
        {
            cur = (BLK) &(q->addr[q->msize]);

            if( cur == p )
            {
                q->msize +=  p->msize + sizeof(struct memblk);
                q->next = p->next;

                p = q;
            }
        }
    }
}

void mfree(void *ret)
{
     BLK p, q, temp, temp1;

    if( ret == NULL || (ripAddr && (ret > (void *)ripAddr)))
        return;

    coalesce();
    q = p = AL;
    while(p && (p->addr != ret))
    {
        q = p;
        p = p->next;
    }
    if(p)
    {

        if( q == p)
        {
            AL =  p->next;
        }

        else
        {
            q->next = p->next;
        }
	memcount-=p->msize;
        temp=FL;
	while(temp)
	{
		
		if(p->addr < temp->addr && temp == FL)
		{
			p->next=FL;
			FL = p;
			break;
		}
		else if(p->addr < temp->addr)
		{
			p->next=temp;
			temp1->next=p;
			break;
		}
		temp1=temp;
		temp=temp->next;
	}
   }
	
	
}
