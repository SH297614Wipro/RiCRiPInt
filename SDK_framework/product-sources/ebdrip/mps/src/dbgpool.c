/* impl.c.dbgpool: POOL DEBUG MIXIN
 *
 * $Id: dbgpool.c,v 1.28.1.1.1.1 2013/12/19 11:27:06 anon Exp $
 * $HopeName: MMsrc!dbgpool.c(EBDSDK_P.1) $
 * Copyright (c) 2001 Ravenbrook Limited.
 * Copyright (C) 2014 Global Graphics Software Ltd. All rights reserved.
 *
 * .source: design.mps.object-debug
 */

#include "dbgpool.h"
#include "poolmfs.h"
#include "splay.h"
#include "mpm.h"
#include <stdarg.h>

SRCID(dbgpool, "$Id: dbgpool.c,v 1.28.1.1.1.1 2013/12/19 11:27:06 anon Exp $");


static void fenceCheckingStep(Addr addr, Size size, Format fmt,
                              Pool pool, DebugInfo info, void *p);


/* tagStruct -- tags for storing info about allocated objects */

typedef struct tagStruct {
  /* We don't want to pay the expense of a sig in every tag */
  Addr addr;
  Size size;
  SplayNodeStruct splayNode;
  DebugInfoStruct info; /* actually variable length */
} tagStruct;

#define SplayNode2Tag(node) PARENT(tagStruct, splayNode, (node))

typedef tagStruct *Tag;


/* TagComp -- splay comparison function for address ordering of tags */

static Compare TagComp(void *key, SplayNode node)
{
  Addr addr1, addr2;

  addr1 = *(Addr *)key;
  addr2 = SplayNode2Tag(node)->addr;
  if (addr1 < addr2)
    return CompareLESS;
  else if (addr1 > addr2) {
    /* Check key is not inside the object of this tag */
    AVER_CRITICAL(AddrAdd(addr2, SplayNode2Tag(node)->size) <= addr1);
    return CompareGREATER;
  } else
    return CompareEQUAL;
}


/* PoolDebugMixinCheck -- check a PoolDebugMixin */

Bool PoolDebugMixinCheck(PoolDebugMixin debug)
{
  /* Nothing to check about fenceTemplate */
  /* Nothing to check about fenceSize */
  /* Nothing to check about freeTemplate */
  /* Nothing to check about freeSize */
  if (debug->keepTags) {
    /* Nothing to check about tagSize */
    CHECKD(Pool, debug->tagPool);
    CHECKL(CHECKTYPE(Addr, void*)); /* tagPool relies on this */
    /* Nothing to check about missingTags */
    CHECKL(SplayTreeCheck(&debug->index));
  }
  UNUSED(debug); /* see impl.c.mpm.check.unused */
  return TRUE;
}


/* DebugPoolDebugMixin -- gets the debug mixin, if any */

#define DebugPoolDebugMixin(pool) (((pool)->class->debugMixin)(pool))


/* PoolDebugOptionsCheck -- check a PoolDebugOptions */

static Bool PoolDebugOptionsCheck(PoolDebugOptions opt)
{
  CHECKL(opt != NULL);
  if (opt->fenceSize != 0) {
    CHECKL(opt->fenceTemplate != NULL);
    /* Nothing to check about fenceSize */
  }
  if (opt->freeSize != 0) {
    CHECKL(opt->freeTemplate != NULL);
    /* Nothing to check about freeSize */
  }
  return TRUE;
}


/* DebugPoolInit -- init method for a debug pool
 *
 * Someday, this could be split into fence and tag init methods.
 */

static Res DebugPoolInit(Pool pool, va_list args)
{
  Res res;
  PoolDebugOptions options;
  PoolDebugMixin debug;

  AVERT(Pool, pool);
  options = va_arg(args, PoolDebugOptions);
  AVERT(PoolDebugOptions, options);

  res = SuperclassOfPool(pool)->init(pool, args);
  if (res != ResOK)
    return res;

  debug = DebugPoolDebugMixin(pool);
  AVER(debug != NULL);
  debug->keepTags = options->keepTags;

  /* fencepost init */
  /* @@@@ This parses a user argument, options, so it should really */
  /* go through the MPS interface.  The template needs to be copied */
  /* into Addr memory, to avoid breaking design.mps.type.addr.use. */
  debug->fenceSize = options->fenceSize;
  if (debug->fenceSize != 0) {
    if (debug->fenceSize % PoolAlignment(pool) != 0) {
      res = ResPARAM;
      goto alignFail;
    }
    /* Fenceposting turns on tagging */
    debug->keepTags = TRUE;
    debug->fenceTemplate = options->fenceTemplate;
  }

  /* free-checking init */
  /* @@@@ This parses a user argument, options, so it should really */
  /* go through the MPS interface.  The template needs to be copied */
  /* into Addr memory, to avoid breaking design.mps.type.addr.use. */
  debug->freeSize = options->freeSize;
  if (debug->freeSize != 0) {
    if (PoolAlignment(pool) % debug->freeSize != 0) {
      res = ResPARAM;
      goto alignFail;
    }
    debug->freeTemplate = options->freeTemplate;
  }
  
  /* tag init */
  if (debug->keepTags) {
    debug->tagSize = offsetof(tagStruct, info) + options->debugInfoSize;
    /* This pool has to be like the arena control pool: the blocks */
    /* allocated must be accessible using void*. */
    res = PoolCreate(&debug->tagPool, PoolArena(pool), PoolClassMFS(),
                     debug->tagSize, debug->tagSize);
    if (res != ResOK)
      goto tagFail;
    debug->missingTags = 0;
    SplayTreeInit(&debug->index, TagComp, NULL);
  }

  debug->sig = PoolDebugMixinSig;
  AVERT(PoolDebugMixin, debug);
  return ResOK;

tagFail:
alignFail:
  SuperclassOfPool(pool)->finish(pool);
  return res;
}


/* DebugPoolFinish -- finish method for a debug pool */

static void DebugPoolFinish(Pool pool)
{
  PoolDebugMixin debug;

  AVERT(Pool, pool);

  debug = DebugPoolDebugMixin(pool);
  AVER(debug != NULL);
  AVERT(PoolDebugMixin, debug);
  if (debug->keepTags) {
    SplayTreeFinish(&debug->index);
    PoolDestroy(debug->tagPool);
  }
  SuperclassOfPool(pool)->finish(pool);
}


/* DebugPoolClear -- clear method for a debug pool */

static void DebugPoolClear(Pool pool)
{
  PoolDebugMixin debug;

  AVERT(Pool, pool);

  debug = DebugPoolDebugMixin(pool);
  AVER(debug != NULL);
  AVERT(PoolDebugMixin, debug);

  /* Splatting is left to the caller, because this only knows about allocated
     blocks if tagging is on. */
  DebugPoolCheckFreeSpace(pool);
  if (debug->fenceSize != 0)
    TagWalk(pool, fenceCheckingStep, (void *)debug);
  if (debug->keepTags) {
    PoolClear(debug->tagPool);
    debug->missingTags = 0;
    SplayTreeInit(&debug->index, TagComp, NULL);
  }

  SuperclassOfPool(pool)->clear(pool);
}


/* freeSplat -- splat free block with splat pattern
 *
 * If base is in a segment, the whole block has to be in it.
 */

static void freeSplat(PoolDebugMixin debug, Pool pool, Addr base, Addr limit)
{
  Addr p, next;
  Size freeSize = debug->freeSize;
  Arena arena;
  Seg seg;
  Bool inSeg;

  AVER(base < limit);

  /* If the block is in a segment, make sure any shield is up. */
  arena = PoolArena(pool);
  inSeg = SegOfAddr(&seg, arena, base);
  if (inSeg) {
    /* The block should fit in the segment in pools that use shields. */
    AVER(!SegIsShielded(seg) || limit <= SegLimit(seg));
    ShieldExpose(arena, seg);
  }
  /* Write as many copies of the template as fit in the block. */
  for (p = base, next = AddrAdd(p, freeSize);
       next <= limit && p < next /* watch out for overflow in next */;
       p = next, next = AddrAdd(next, freeSize))
    (void)AddrCopy(p, debug->freeTemplate, freeSize);
  /* Fill the tail of the block with a partial copy of the template. */
  if (next > limit || next < p)
    (void)AddrCopy(p, debug->freeTemplate, AddrOffset(p, limit));
  if (inSeg) {
    ShieldCover(arena, seg);
  }
}


/* freeCheck -- check free block for splat pattern */

static Bool freeCheck(PoolDebugMixin debug, Pool pool, Addr base, Addr limit)
{
  Addr p, next;
  Size freeSize = debug->freeSize;
  Res res;
  Arena arena;
  Seg seg;
  Bool inSeg;

  AVER(base < limit);

  /* If the block is in a segment, make sure any shield is up. */
  arena = PoolArena(pool);
  inSeg = SegOfAddr(&seg, arena, base);
  if (inSeg) {
    /* The block should fit in the segment in pools that use shields. */
    AVER(!SegIsShielded(seg) || limit <= SegLimit(seg));
    ShieldExpose(arena, seg);
  }
  /* Compare this to the AddrCopys in freeSplat. */
  /* Check the complete copies of the template in the block. */
  for (p = base, next = AddrAdd(p, freeSize);
       next <= limit && p < next /* watch out for overflow in next */;
       p = next, next = AddrAdd(next, freeSize))
    if (AddrComp(p, debug->freeTemplate, freeSize) != 0) {
      res = FALSE; goto done;
    }
  /* Check the partial copy of the template at the tail of the block. */
  if (next > limit || next < p)
    if (AddrComp(p, debug->freeTemplate, AddrOffset(p, limit)) != 0) {
      res = FALSE; goto done;
    }
  res = TRUE;

done:
  if (inSeg) {
    ShieldCover(arena, seg);
  }
  return res;
}


/* freeCheckAlloc -- allocation wrapper for free-checking */

static Res freeCheckAlloc(Addr *aReturn, PoolDebugMixin debug, Pool pool,
                          Size size, Bool withReservoir)
{
  Res res;
  Addr new;

  AVER(aReturn != NULL);

  res = SuperclassOfPool(pool)->alloc(&new, pool, size, withReservoir, NULL);
  if (res != ResOK)
    return res;
  if (debug->freeSize != 0)
    ASSERT(freeCheck(debug, pool, new, AddrAdd(new, size)),
           "free space corrupted on alloc");

  *aReturn = new;
  return res;
}


/* freeCheckFree -- freeing wrapper for free-checking */

static void freeCheckFree(PoolDebugMixin debug,
                          Pool pool, Addr old, Size size)
{
  if (debug->freeSize != 0)
    freeSplat(debug, pool, old, AddrAdd(old, size));
  SuperclassOfPool(pool)->free(pool, old, size);
}


/* fenceAlloc -- allocation wrapper for fenceposts
 *
 * Allocates an object, adding fenceposts on both sides.  Layout:
 *
 * |----------|-------------------------------------|------|----------|
 *   start fp              client object              slop    end fp
 *
 * slop is the extra allocation from rounding up the client request to
 * the pool's alignment.  The fenceposting code does this, so there's a
 * better chance of the end fencepost being flush with the next object
 * (can't be guaranteed, since the underlying pool could have allocated
 * an even larger block).  The alignment slop is filled from the
 * fencepost template as well (as much as fits, .fence.size guarantees
 * the template is larger).
 */

static Res fenceAlloc(Addr *aReturn, PoolDebugMixin debug, Pool pool,
                      Size size, Bool withReservoir)
{
  Res res;
  Addr new = NULL /* pacify compiler */, clientNew;
  Size alignedSize;

  AVER(aReturn != NULL);

  alignedSize = SizeAlignUp(size, PoolAlignment(pool));
  res = freeCheckAlloc(&new, debug, pool, alignedSize + 2*debug->fenceSize,
                       withReservoir);
  if (res != ResOK)
    return res;
  clientNew = AddrAdd(new, debug->fenceSize);
  /* @@@@ shields? */
  /* start fencepost */
  (void)AddrCopy(new, debug->fenceTemplate, debug->fenceSize);
  /* alignment slop */
  (void)AddrCopy(AddrAdd(clientNew, size),
                 debug->fenceTemplate, alignedSize - size);
  /* end fencepost */
  (void)AddrCopy(AddrAdd(clientNew, alignedSize),
                 debug->fenceTemplate, debug->fenceSize);

  *aReturn = clientNew;
  return res;
}


/* fenceCheck -- check fences of an object */

static Bool fenceCheck(PoolDebugMixin debug, Pool pool, Addr obj, Size size)
{
  Size alignedSize;

  AVERT_CRITICAL(PoolDebugMixin, debug);
  AVERT_CRITICAL(Pool, pool);
  /* Can't check obj */

  alignedSize = SizeAlignUp(size, PoolAlignment(pool));
  /* @@@@ shields? */
  /* Compare this to the AddrCopys in fenceAlloc */
  return (AddrComp(AddrSub(obj, debug->fenceSize), debug->fenceTemplate,
                   debug->fenceSize) == 0
          && AddrComp(AddrAdd(obj, size), debug->fenceTemplate,
                      alignedSize - size) == 0
          && AddrComp(AddrAdd(obj, alignedSize), debug->fenceTemplate,
                      debug->fenceSize) == 0);
}


/* fenceFree -- freeing wrapper for fenceposts */

static void fenceFree(PoolDebugMixin debug,
                      Pool pool, Addr old, Size size)
{
  Size alignedSize;

  ASSERT(fenceCheck(debug, pool, old, size), "fencepost check on free");

  alignedSize = SizeAlignUp(size, PoolAlignment(pool));
  freeCheckFree(debug, pool, AddrSub(old, debug->fenceSize),
                alignedSize + 2*debug->fenceSize);
}


/* tagAlloc -- allocation wrapper for tagged pools */

static Res tagAlloc(PoolDebugMixin debug,
                    Pool pool, Addr new, Size size,
                    Bool withReservoir, DebugInfo info)
{
  Tag tag;
  Res res;
  Addr p;

  UNUSED(pool);
  res = PoolAlloc(&p, debug->tagPool, debug->tagSize, FALSE, NULL);
  if (res != ResOK) {
    if (withReservoir) { /* design.mps.object-debug.out-of-space */
      debug->missingTags++;
      return ResOK;
    } else {
      return res;
    }
  }
  tag = (Tag)p;
  tag->addr = new; tag->size = size;
  SplayNodeInit(&tag->splayNode);
  if (info != NULL)
    (void)mps_lib_memcpy(&tag->info, info,
                         debug->tagSize - offsetof(tagStruct, info));
  res = SplayTreeInsert(&debug->index, &tag->splayNode, (void *)&new);
  AVER(res == ResOK);
  return ResOK;
}


/* tagFree -- deallocation wrapper for tagged pools */

static void tagFree(PoolDebugMixin debug, Pool pool, Addr old, Size size)
{
  SplayNode node;
  Tag tag;
  Res res;

  AVERT(PoolDebugMixin, debug);
  AVERT(Pool, pool);
  AVER(size > 0);

  res = SplayTreeSearch(&node, &debug->index, (void *)&old);
  if (res != ResOK) {
    AVER(debug->missingTags > 0);
    debug->missingTags--;
    return;
  }
  tag = SplayNode2Tag(node);
  AVER(tag->size == size);
  res = SplayTreeDelete(&debug->index, node, (void *)&old);
  AVER(res == ResOK);
  SplayNodeFinish(node);
  PoolFree(debug->tagPool, (Addr)tag, debug->tagSize);
}


/* DebugPoolAlloc -- alloc method for a debug pool */

static Res DebugPoolAlloc(Addr *aReturn, Pool pool, Size size,
                          Bool withReservoir, DebugInfo info)
{
  Res res;
  Addr new = NULL /* pacify compiler */;
  PoolDebugMixin debug;

  AVER(aReturn != NULL);
  AVERT(Pool, pool);
  AVER(size > 0);
  AVERT(Bool, withReservoir);

  debug = DebugPoolDebugMixin(pool);
  AVER(debug != NULL);
  AVERT(PoolDebugMixin, debug);
  if (debug->fenceSize != 0)
    res = fenceAlloc(&new, debug, pool, size, withReservoir);
  else
    res = freeCheckAlloc(&new, debug, pool, size, withReservoir);
  if (res != ResOK)
    return res;
  /* Allocate object first, so it fits even when the tag doesn't. */
  if (debug->keepTags) {
    res = tagAlloc(debug, pool, new, size, withReservoir, info);
    if (res != ResOK)
      goto tagFail;
  }

  *aReturn = new;
  return res;

tagFail:
  if (debug->fenceSize != 0)
    fenceFree(debug, pool, new, size);
  else
    freeCheckFree(debug, pool, new, size);
  return res;
}


/* DebugPoolFree -- free method for a debug pool */

static void DebugPoolFree(Pool pool, Addr old, Size size)
{
  PoolDebugMixin debug;

  AVERT(Pool, pool);
  /* Can't check old */
  AVER(size > 0);

  debug = DebugPoolDebugMixin(pool);
  AVER(debug != NULL);
  AVERT(PoolDebugMixin, debug);

  if (debug->fenceSize != 0)
    fenceFree(debug, pool, old, size);
  else
    freeCheckFree(debug, pool, old, size);
  /* Free the object first, to get fences checked before tag. */
  if (debug->keepTags)
    tagFree(debug, pool, old, size);
}


/* TagWalk -- walk all objects in the pool using tags */


#define ObjectsStepMethodCheck(f) \
  ((f) != NULL) /* that's the best we can do */

void TagWalk(Pool pool, ObjectsStepMethod step, void *p)
{
  SplayNode node;
  PoolDebugMixin debug;

  AVERT(Pool, pool);
  AVERT(ObjectsStepMethod, step);
  /* Can't check p */

  debug = DebugPoolDebugMixin(pool);
  AVER(debug != NULL);
  AVERT(PoolDebugMixin, debug); 

  node = SplayTreeFirst(&debug->index);
  while (node != NULL) {
    Tag tag = SplayNode2Tag(node);

    step(tag->addr, tag->size, NULL, pool, &tag->info, p);
    node = SplayTreeNext(&debug->index, node, (void *)&tag->addr);
  }
}


/* fenceCheckingStep -- step function for DebugPoolCheckFences */

static void fenceCheckingStep(Addr addr, Size size, Format fmt,
                              Pool pool, DebugInfo info, void *p)
{
  /* no need to check arguments checked in the caller */
  UNUSED(fmt); UNUSED(info);
  ASSERT(fenceCheck((PoolDebugMixin)p, pool, addr, size),
         "fencepost check requested by client");
}


/* DebugPoolCheckFences -- check all the fenceposts in the pool */

void DebugPoolCheckFences(Pool pool)
{
  PoolDebugMixin debug;

  AVERT(Pool, pool);
  debug = DebugPoolDebugMixin(pool);
  if (debug == NULL)
    return;
  AVERT(PoolDebugMixin, debug);

  if (debug->fenceSize != 0)
    TagWalk(pool, fenceCheckingStep, (void *)debug);
}


/* DebugPoolFreeSplat -- if in a free-checking debug pool, splat free block */

void DebugPoolFreeSplat(Pool pool, Addr base, Addr limit)
{
  PoolDebugMixin debug;

  AVERT(Pool, pool);
  AVER(PoolHasAddr(pool, base));
  AVER(PoolHasAddr(pool, AddrSub(limit, 1)));

  debug = DebugPoolDebugMixin(pool);
  if (debug != NULL) {
    AVERT(PoolDebugMixin, debug);
    if (debug->freeSize != 0)
      freeSplat(debug, pool, base, limit);
  }
}


/* DebugPoolFreeCheck -- if in a free-checking debug pool, check free block */

void DebugPoolFreeCheck(Pool pool, Addr base, Addr limit)
{
  PoolDebugMixin debug;

  AVERT(Pool, pool);
  AVER(PoolHasAddr(pool, base));
  AVER(PoolHasAddr(pool, AddrSub(limit, 1)));

  debug = DebugPoolDebugMixin(pool);
  if (debug != NULL) {
    AVERT(PoolDebugMixin, debug);
    if (debug->freeSize != 0)
      ASSERT(freeCheck(debug, pool, base, limit),
             "free space corrupted on release");
  }
}


/* freeCheckingStep -- step function for DebugPoolCheckFreeSpace */

void freeCheckingStep(Addr base, Addr limit, Pool pool, void *p)
{
  /* no need to check arguments checked in the caller */
  ASSERT(freeCheck((PoolDebugMixin)p, pool, base, limit),
         "free space corrupted on client check");
}


/* DebugPoolCheckFreeSpace -- check free space in the pool for overwrites */

void DebugPoolCheckFreeSpace(Pool pool)
{
  PoolDebugMixin debug;

  AVERT(Pool, pool);
  debug = DebugPoolDebugMixin(pool);
  if (debug == NULL)
    return;
  AVERT(PoolDebugMixin, debug);

  if (debug->freeSize != 0)
    PoolFreeWalk(pool, freeCheckingStep, (void *)debug);
}


/* PoolClassMixInDebug -- mix in the debug support for class init */

void PoolClassMixInDebug(PoolClass class)
{
  /* Can't check class because it's not initialized yet */
  class->init = DebugPoolInit;
  class->finish = DebugPoolFinish;
  class->clear = DebugPoolClear;
  class->alloc = DebugPoolAlloc;
  class->free = DebugPoolFree;
}
