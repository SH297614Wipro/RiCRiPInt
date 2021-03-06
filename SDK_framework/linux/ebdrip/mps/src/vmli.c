/* impl.c.vmli: VIRTUAL MEMORY MAPPING FOR LINUX
 *
 * $Id: vmli.c,v 1.13.11.1.1.1 2013/12/19 11:27:09 anon Exp $
 * $HopeName: MMsrc!vmli.c(EBDSDK_P.1) $
 * Copyright (c) 2001 Ravenbrook Limited.
 * Copyright (C) 2002-2007 Global Graphics Software Ltd. All rights reserved.
 *Global Graphics Software Ltd. Confidential Information.
 *
 * .purpose: This is the implementation of the virtual memory mapping 
 * interface (vm.h) for Linux.  It was created by copying vmo1.c (the 
 * DIGITAL UNIX implementation) as that seemed to be closest.
 *
 * .design: See design.mps.vm.  .design.linux: mmap(2) is used to
 * reserve address space by creating a mapping with page access none.
 * mmap(2) is used to map pages onto store by creating a copy-on-write
 * (MAP_PRIVATE) mapping with the flag MAP_ANONYMOUS.
 *
 * .assume.not-last: The implementation of VMCreate assumes that
 * mmap() will not choose a region which contains the last page
 * in the address space, so that the limit of the mapped area
 * is representable.
 *
 * .assume.mmap.err: ENOMEM is the only error we really expect to get
 * from mmap.  The others are either caused by invalid params or
 * features we don't use.  See mmap(2) for details.  However, it appears
 * return EINVAL when the size is > 3 GB, so allow that.
 *
 * .assume.off_t: We assume that the Size type (defined by the MM) fits
 * in the off_t type (define by the system (POSIX?)).  In fact we test
 * the more stringent requirement that they are the same size.  This
 * assumption is made in VMUnmap.
 *
 * .remap: Possibly this should use mremap to reduce the number of
 * distinct mappings.  According to our current testing, it doesn't
 * seem to be a problem.  */

/* Use all extensions */
#define _GNU_SOURCE 1

/* for open(2) */
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

/* for mmap(2), munmap(2) */
#include <sys/mman.h>

/* for errno(2) */
#include <errno.h>

/* for sysconf(2), close(2) */
#include <unistd.h>

#include "mpm.h"


#ifndef MPS_OS_LI
#error "vmli.c is LINUX specific, but MPS_OS_LI is not set"
#endif

SRCID(vmli, "$Id: vmli.c,v 1.13.11.1.1.1 2013/12/19 11:27:09 anon Exp $");


/* VMStruct -- virtual memory structure */

#define VMSig           ((Sig)0x519B3999) /* SIGnature VM */

typedef struct VMStruct {
  Sig sig;                      /* design.mps.sig */
  Align align;                  /* page size */
  Addr base, limit;             /* boundaries of reserved space */
  Size reserved;                /* total reserved address space */
  Size mapped;                  /* total mapped memory */
} VMStruct;


/* VMAlign -- return page size */

Align VMAlign(VM vm)
{
  AVERT(VM, vm);

  return vm->align;
}


/* VMCheck -- check a VM */

Bool VMCheck(VM vm)
{
  CHECKS(VM, vm);
  CHECKL(vm->base != 0);
  CHECKL(vm->limit != 0);
  CHECKL(vm->base < vm->limit);
  CHECKL(vm->mapped <= vm->reserved);
  CHECKL(SizeIsP2(vm->align));
  CHECKL(AddrIsAligned(vm->base, vm->align));
  CHECKL(AddrIsAligned(vm->limit, vm->align));
  return TRUE;
}


/* VMCreate -- reserve some virtual address space, and create a VM structure */

Res VMCreate(VM *vmReturn, Size size)
{
  Align align;
  VM vm;
  long pagesize;
  void *addr;
  Res res;

  AVER(vmReturn != NULL);

  /* sysconf code copied wholesale from vmso.c */
  /* Find out the page size from the OS */
  pagesize = sysconf(_SC_PAGESIZE);
  /* check the actual returned pagesize will fit in an object of */
  /* type Align. */
  AVER(pagesize > 0);
  AVER((unsigned long)pagesize <= (unsigned long)(Align)-1);
  /* Note implicit conversion from "long" to "Align". */
  align = pagesize;
  AVER(SizeIsP2(align));
  size = SizeAlignUp(size, align);
  if((size == 0) || (size > (Size)(size_t)-1))
    return ResRESOURCE;

  /* Map in a page to store the descriptor on. */
  addr = mmap(0, (size_t)SizeAlignUp(sizeof(VMStruct), align),
              PROT_READ | PROT_WRITE,
              MAP_ANONYMOUS | MAP_PRIVATE,
              -1, 0);
  if(addr == MAP_FAILED) {
    int e = errno;
    AVER(e == ENOMEM); /* .assume.mmap.err */
    return ResMEMORY;
  }
  vm = (VM)addr;

  vm->align = align;

  /* See .assume.not-last. */
  addr = mmap(0, (size_t)size,
              PROT_NONE, MAP_ANONYMOUS | MAP_PRIVATE,
              -1, 0);
  if(addr == MAP_FAILED) {
    int e = errno;
    AVER(e == ENOMEM || e == EINVAL); /* .assume.mmap.err */
    res = (e == ENOMEM || e == EINVAL) ? ResRESOURCE : ResFAIL;
    goto failReserve;
  }

  vm->base = (Addr)addr;
  vm->limit = AddrAdd(vm->base, size);
  vm->reserved = size;
  vm->mapped = (Size)0;

  vm->sig = VMSig;

  AVERT(VM, vm);

  EVENT_PAA(VMCreate, vm, vm->base, vm->limit);

  *vmReturn = vm;
  return ResOK;

failReserve:
  (void)munmap((void *)vm, (size_t)SizeAlignUp(sizeof(VMStruct), align));
  return res;
}


/* VMDestroy -- release all address space and destroy VM structure */

void VMDestroy(VM vm)
{
  int r;

  AVERT(VM, vm);
  AVER(vm->mapped == (Size)0);

  /* This appears to be pretty pointless, since the descriptor */
  /* page is about to vanish completely.  However, munmap might fail */
  /* for some reason, and this would ensure that it was still */
  /* discovered if sigs were being checked. */
  vm->sig = SigInvalid;

  r = munmap((void *)vm->base, (size_t)AddrOffset(vm->base, vm->limit));
  AVER(r == 0);
  r = munmap((void *)vm,
             (size_t)SizeAlignUp(sizeof(VMStruct), vm->align));
  AVER(r == 0);

  EVENT_P(VMDestroy, vm);
}


/* VMBase -- return the base address of the memory reserved */

Addr VMBase(VM vm)
{
  AVERT(VM, vm);

  return vm->base;
}


/* VMLimit -- return the limit address of the memory reserved */

Addr VMLimit(VM vm)
{
  AVERT(VM, vm);

  return vm->limit;
}


/* VMReserved -- return the amount of memory reserved */

Size VMReserved(VM vm)
{
  AVERT(VM, vm);

  return vm->reserved;
}


/* VMMapped -- return the amount of memory actually mapped */

Size VMMapped(VM vm)
{
  AVERT(VM, vm);

  return vm->mapped;
}


/* VMMap -- map the given range of memory */

Res VMMap(VM vm, Addr base, Addr limit)
{
  Size size;

  AVERT(VM, vm);
  AVER(sizeof(void *) == sizeof(Addr));
  AVER(base < limit);
  AVER(base >= vm->base);
  AVER(limit <= vm->limit);
  AVER(AddrIsAligned(base, vm->align));
  AVER(AddrIsAligned(limit, vm->align));

  size = AddrOffset(base, limit);

  if(mmap((void *)base, (size_t)size,
          PROT_READ | PROT_WRITE | PROT_EXEC,
          MAP_ANONYMOUS | MAP_PRIVATE | MAP_FIXED,
          -1, 0)
     == MAP_FAILED) {
    AVER(errno == ENOMEM); /* .assume.mmap.err */
    return ResMEMORY;
  }

  vm->mapped += size;

  EVENT_PAA(VMMap, vm, base, limit);
  return ResOK;
}


/* VMUnmap -- unmap the given range of memory */

void VMUnmap(VM vm, Addr base, Addr limit)
{
  Size size;
  void *addr;

  AVERT(VM, vm);
  AVER(base < limit);
  AVER(base >= vm->base);
  AVER(limit <= vm->limit);
  AVER(AddrIsAligned(base, vm->align));
  AVER(AddrIsAligned(limit, vm->align));
  AVER(sizeof(off_t) == sizeof(Size));  /* .assume.off_t */

  size = AddrOffset(base, limit);

  /* see design.mps.vmo1.fun.unmap.offset */
  addr = mmap((void *)base, (size_t)size,
              PROT_NONE, MAP_ANONYMOUS | MAP_PRIVATE | MAP_FIXED,
              -1, 0);
  AVER(addr == (void *)base);

  vm->mapped -= size;

  EVENT_PAA(VMUnmap, vm, base, limit);
}
