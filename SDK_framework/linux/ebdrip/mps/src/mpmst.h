/* impl.h.mpmst: MEMORY POOL MANAGER DATA STRUCTURES
 *
 * $Id: mpmst.h,v 1.109.1.1.1.1 2013/12/19 11:27:09 anon Exp $
 * $HopeName: MMsrc!mpmst.h(EBDSDK_P.1) $
 * Copyright (c) 2001 Ravenbrook Limited.
 * Copyright (C) 2014 Global Graphics Software Ltd. All rights reserved.
 *
 * .design: This header file crosses module boundaries.  The relevant
 * design a module's structures should be found in that module's design
 * document.
 *
 * .structure: Most structures have already been declared as incomplete
 * types in impl.h.mpmtypes.  Most of the structures are the underlying
 * aggregate types for an abstract data type.  See
 * guide.impl.c.naming.type.adt-aggregate.relate.
 *
 * .rationale.sig: Object signatures (PoolSig, etc.) are defined here,
 * along with the structures, so that any code which can see a structure
 * can also check its signature before using any of its fields.  See
 * design.mps.sig.test.uniq to check that signatures are unique.  */

#ifndef mpmst_h
#define mpmst_h

#include "config.h"
#include "mpmtypes.h"

#include "protocol.h"
#include "ring.h"
#include "chain.h"


/* PoolClassStruct -- pool class structure
 *
 * See design.mps.pool.
 *
 * .class: The pool class structure is defined by each pool class
 * implementation in order to provide an interface between the MPM
 * and the class (see design.mps.class-interface) via generic
 * functions (see impl.c.pool).  A class XXX defines a function
 * PoolClassXXX() returning a PoolClass pointing to a PoolClassStruct
 * of methods which implement the memory management policy.
 *
 * .class.end-sig: The class structure has a signature at the end.  This
 * causes the compiler to complain if the class structure is extended
 * without modifying static initializers.  */

#define PoolClassSig    ((Sig)0x519C7A55) /* SIGnature pool CLASS */

typedef struct PoolClassStruct {
  ProtocolClassStruct protocol;
  const char *name;             /* class name string */
  size_t size;                  /* size of outer structure */
  size_t offset;                /* offset of generic struct in outer struct */
  Attr attr;                    /* attributes */
  PoolInitMethod init;          /* initialize the pool descriptor */
  PoolFinishMethod finish;      /* finish the pool descriptor */
  PoolClearMethod clear;        /* clear all memory from pool */
  PoolAllocMethod alloc;        /* allocate memory from pool */
  PoolFreeMethod free;          /* free memory to pool */
  PoolBufferFillMethod bufferFill;      /* out-of-line reserve */
  PoolBufferEmptyMethod bufferEmpty;    /* out-of-line commit */
  PoolAccessMethod access;      /* handles read/write accesses */
  PoolWhitenMethod whiten;      /* whiten objects in a segment */
  PoolGreyMethod grey;          /* grey non-white objects */
  PoolBlackenMethod blacken;    /* blacken grey objects without scanning */
  PoolScanMethod scan;          /* find references during tracing */
  PoolFixMethod fix;            /* referent reachable during tracing */
  PoolFixEmergencyMethod fixEmergency;  /* as fix, no failure allowed */
  PoolResolveMethod resolve;    /* referent updated during tracing */
  PoolReclaimMethod reclaim;    /* reclaim dead objects after tracing */
  PoolRampBeginMethod rampBegin;/* begin a ramp pattern */
  PoolRampEndMethod rampEnd;    /* end a ramp pattern */
  PoolFramePushMethod framePush; /* push an allocation frame */
  PoolFramePopMethod framePop;  /* pop an allocation frame */
  PoolFramePopPendingMethod framePopPending;  /* notify pending pop */
  PoolWalkMethod walk;          /* walk over a segment */
  PoolFreeWalkMethod freewalk;  /* walk over free blocks */
  PoolBufferClassMethod bufferClass; /* default BufferClass of pool */
  PoolFreeSizeMethod freeSize;  /* size of free space in the pool */
  PoolDescribeMethod describe;  /* describe the contents of the pool */
  PoolDebugMixinMethod debugMixin; /* find the debug mixin, if any */
  Bool labelled;                /* whether it has been EventLabelled */
  Sig sig;                      /* .class.end-sig */
} PoolClassStruct;


typedef PoolClassStruct AbstractPoolClassStruct;
typedef PoolClassStruct AbstractAllocFreePoolClassStruct;
typedef PoolClassStruct AbstractBufferPoolClassStruct;
typedef PoolClassStruct AbstractSegBufPoolClassStruct;
typedef PoolClassStruct AbstractScanPoolClassStruct;
typedef PoolClassStruct AbstractCollectPoolClassStruct;


/* PoolStruct -- generic structure
 *
 * .pool: A generic structure is created when a pool is created and
 * holds the generic part of the pool's state.  Each pool class defines
 * a "subclass" of the pool structure (the "outer structure") which
 * contains PoolStruct as a a field.  The outer structure holds the
 * class-specific part of the pool's state.  See impl.c.pool,
 * design.mps.pool.  */

#define PoolSig         ((Sig)0x519B0019) /* SIGnature POOL */

typedef struct PoolStruct {     /* generic structure */
  Sig sig;                      /* design.mps.sig */
  Serial serial;                /* from arena->poolSerial */
  PoolClass class;              /* pool class structure */
  Arena arena;                  /* owning arena */
  RingStruct arenaRing;         /* link in list of pools in arena */
  RingStruct bufferRing;        /* allocation buffers are attached to pool */
  Serial bufferSerial;          /* serial of next buffer */
  RingStruct segRing;           /* segs are attached to pool */
  Align alignment;              /* alignment for units */
  Format format;                /* format only if class->attr&AttrFMT */
  PoolFixMethod fix;            /* fix method */
  Size managedSize;             /* size of memory managed */
  double fillMutatorSize;       /* bytes filled, mutator buffers */
  double emptyMutatorSize;      /* bytes emptied, mutator buffers */
  double fillInternalSize;      /* bytes filled, internal buffers */
  double emptyInternalSize;     /* bytes emptied, internal buffers */
} PoolStruct;


/* MFSStruct -- MFS (Manual Fixed Small) pool outer structure
 *
 * .mfs: See impl.c.poolmfs, design.mps.poolmfs.
 *
 * The MFS outer structure is declared here because it is inlined
 * in the control pool structure which is inlined in the arena.  Normally,
 * pool outer structures are declared with the pools.
 *
 * The signature is placed at the end, see
 * design.mps.pool.outer-structure.sig. */

#define MFSSig          ((Sig)0x5193F599) /* SIGnature MFS */

typedef struct MFSStruct {      /* MFS outer structure */
  PoolStruct poolStruct;        /* generic structure */
  Size unroundedUnitSize;       /* the unit size requested */
  Size extendBy;                /* arena alloc size rounded using unitSize */
  Size unitSize;                /* rounded for management purposes */
  Word unitsPerExtent;          /* number of units per arena alloc */
  struct MFSHeaderStruct *freeList; /* head of the free list */
  Tract tractList;              /* the first tract */
  Sig sig;                      /* design.mps.sig */
} MFSStruct;


/* MVStruct -- MV (Manual Variable) pool outer structure
 *
 * .mv: See impl.c.poolmv, design.mps.poolmv.
 *
 * The MV pool outer structure is declared here because it is the
 * control pool structure which is inlined in the arena.  Normally,
 * pool outer structures are declared with the pools.  */

#define MVSig           ((Sig)0x5193B999) /* SIGnature MV */

typedef struct MVStruct {       /* MV pool outer structure */
  PoolStruct poolStruct;        /* generic structure */
  MFSStruct blockPoolStruct;    /* for managing block descriptors */
  MFSStruct spanPoolStruct;     /* for managing span descriptors */
  Size extendBy;                /* segment size to extend pool by */
  Size avgSize;                 /* client estimate of allocation size */
  Size maxSize;                 /* client estimate of maximum size */
  Size space;                   /* total free space in pool */
  Size lost;                    /* design.mps.poolmv.lost */
  RingStruct spans;             /* span chain */
  Sig sig;                      /* design.mps.sig */
} MVStruct;


/* ReservoirStruct -- Reservoir structure
 *
 * .reservoir: See impl.c.reserv, design.mps.reservoir.
 *
 * The Reservoir structure is declared here because it is in-lined in
 * the arena for storing segments for the low-memory reservoir.  It is
 * implemented as a pool - but doesn't follow the normal pool naming
 * conventions because it's not intended for general use and the use of
 * a pool is an incidental detail.  */

#define ReservoirSig ((Sig)0x5196e599) /* SIGnature REServoir */

typedef struct ReservoirStruct {   /* Reservoir structure */
  PoolStruct poolStruct;        /* generic pool structure */
  Tract reserve;                /* linked list of reserve tracts */
  Size reservoirLimit;          /* desired reservoir size */
  Size reservoirSize;           /* actual reservoir size */
  Sig sig;                      /* design.mps.sig */
} ReservoirStruct;


/* MessageClassStruct -- Message Class structure
 *
 * See design.mps.message.class.struct (and design.mps.message.message,
 * and design.mps.message.class).  */

#define MessageClassSig ((Sig)0x519359c1) /* SIGnature MeSsaGe CLass */

typedef struct MessageClassStruct {
  Sig sig;                      /* design.mps.sig */
  const char *name;             /* Human readable Class name */

  /* generic methods */
  MessageDeleteMethod delete;   /* terminates a message */

  /* methods specific to MessageTypeFinalization */
  MessageFinalizationRefMethod finalizationRef;

  /* methods specific to MessageTypeGC */
  MessageGCLiveSizeMethod gcLiveSize;
  MessageGCCondemnedSizeMethod gcCondemnedSize;
  MessageGCNotCondemnedSizeMethod gcNotCondemnedSize;

  Sig endSig;                   /* design.mps.message.class.sig.double */
} MessageClassStruct;

#define MessageSig      ((Sig)0x5193e559) /* SIG MESSaGe */

/* MessageStruct -- Message structure
 *
 * See design.mps.message.message.struct.  */

typedef struct MessageStruct {
  Sig sig;                      /* design.mps.sig */
  Arena arena;                  /* owning arena */
  MessageType type;             /* Message Type */
  MessageClass class;           /* Message Class Structure */
  RingStruct queueRing;         /* Message queue ring */
} MessageStruct;


/* SegClassStruct -- segment class structure
 *
 * See design.mps.seg & design.mps.protocol.
 *
 * .seg.class: The segment class structure is defined by each segment
 * class implementation in order to provide a generic interface to
 * segments.  */

#define SegClassSig    ((Sig)0x5195E9C7) /* SIGnature SEG CLass */

typedef struct SegClassStruct {
  ProtocolClassStruct protocol;
  const char *name;             /* class name string */
  size_t size;                  /* size of outer structure */
  SegInitMethod init;           /* initialize the segment */
  SegFinishMethod finish;       /* finish the segment */
  SegSetSummaryMethod setSummary; /* set the segment summary  */
  SegBufferMethod buffer;       /* get the segment buffer  */
  SegSetBufferMethod setBuffer; /* set the segment buffer  */
  SegSetGreyMethod setGrey;     /* change greyness of segment */
  SegSetWhiteMethod setWhite;   /* change whiteness of segment */
  SegSetRankSetMethod setRankSet; /* change rank set of segment */
  SegSetRankSummaryMethod setRankSummary; /* change rank set & summary */
  SegDescribeMethod describe;   /* describe the contents of the seg */
  SegMergeMethod merge;         /* merge two adjacent segments */
  SegSplitMethod split;         /* split a segment into two */
  Sig sig;                      /* .class.end-sig */
} SegClassStruct;


/* SegStruct -- segment structure
 *
 * .seg: Segments are the basic units of protection and tracer activity
 * for allocated memory.  See design.mps.seg.  */

#define SegSig      ((Sig)0x5195E999) /* SIGnature SEG  */

typedef struct SegStruct {      /* segment structure */
  Sig sig;                      /* impl.h.misc.sig */
  SegClass class;               /* segment class structure */
  Tract firstTract;             /* first tract of segment */
  RingStruct poolRing;          /* link in list of segs in pool */
  Addr limit;                   /* limit of segment */
  unsigned depth : ShieldDepthWIDTH; /* see impl.c.shield.def.depth */
  AccessSet pm : AccessSetWIDTH; /* protection mode, impl.c.shield */
  AccessSet sm : AccessSetWIDTH; /* shield mode, impl.c.shield */
  TraceSet grey : TraceLIMIT;   /* traces for which seg is grey */
  TraceSet white : TraceLIMIT;  /* traces for which seg is white */
  TraceSet nailed : TraceLIMIT; /* traces for which seg has nailed objects */
  RankSet rankSet : RankLIMIT;  /* ranks of references in this seg */
} SegStruct;


/* GCSegStruct -- GCable segment structure
 *
 * .seggc: GCSeg is a subclass of Seg with support for buffered
 * allocation and GC.  See design.mps.seg.  */

#define GCSegSig      ((Sig)0x5199C5E9) /* SIGnature GC SEG  */

typedef struct GCSegStruct {    /* GC segment structure */
  SegStruct segStruct;          /* superclass fields must come first */
  RingStruct greyRing;          /* link in list of grey segs */
  RefSet summary;               /* summary of references out of seg */
  Buffer buffer;                /* non-NULL if seg is buffered */
  Sig sig;                      /* design.mps.sig */
} GCSegStruct;


/* SegPrefStruct -- segment preference structure
 *
 * .seg-pref: arena memory users (pool class code) need a way of
 * expressing preferences about the segments they allocate.
 *
 * .seg-pref.misleading: The name is historical and misleading. SegPref
 * objects need have nothing to do with segments. @@@@ */

#define SegPrefSig      ((Sig)0x5195E9B6) /* SIGnature SEG PRef */

typedef struct SegPrefStruct {  /* segment placement preferences */
  Sig sig;                      /* impl.h.misc.sig */
  Bool high;                    /* high or low */
  ZoneSet zones;                /* preferred zones */
  Bool isCollected;             /* whether segment will be collected */
  Bool isGen;                   /* whether gen is set */
  Serial gen;                   /* associated geneation */
} SegPrefStruct;


/* BufferClassStruct -- buffer class structure
 *
 * See design.mps.buffer & design.mps.protocol.
 *
 * .buffer.class: The buffer class structure is defined by each buffer
 * class implementation in order to provide a generic interface to
 * buffers.  */

#define BufferClassSig    ((Sig)0x519B0FC7) /* SIGnature BUFfer CLass */

typedef struct BufferClassStruct {
  ProtocolClassStruct protocol;
  const char *name;             /* class name string */
  size_t size;                  /* size of outer structure */
  BufferInitMethod init;        /* initialize the buffer */
  BufferFinishMethod finish;    /* finish the buffer */
  BufferAttachMethod attach;    /* attach the buffer */
  BufferDetachMethod detach;    /* detach the buffer */
  BufferDescribeMethod describe;/* describe the contents of the buffer */
  BufferSegMethod seg;          /* seg of buffer */
  BufferRankSetMethod rankSet;  /* rank set of buffer */
  BufferSetRankSetMethod setRankSet; /* change rank set of buffer */
  BufferReassignSegMethod reassignSeg; /* change seg of attached buffer */
  Sig sig;                      /* .class.end-sig */
} BufferClassStruct;




/* APStruct -- allocation point structure
 *
 * AP are part of the design of buffers see design.mps.buffer.
 *
 * The allocation point is exported to the client code so that it can
 * do in-line buffered allocation.
 *
 * .ap: This structure must match impl.h.mps.ap.  See also
 * impl.c.mpsi.check.ap.  */

typedef struct APStruct {
  Addr init;                    /* limit of initialized area */
  Addr alloc;                   /* limit of allocated area */
  Addr limit;                   /* limit of allocation buffer */
  Addr frameptr;                /* lightweight frame pointer */
  Bool enabled;                 /* lightweight frame status */
  Bool lwPopPending;            /* lightweight pop pending? */
} APStruct;


/* BufferStruct -- allocation buffer structure
 *
 * See impl.c.buffer, design.mps.buffer.
 *
 * The buffer contains an AP which may be exported to the client.  */

#define BufferSig       ((Sig)0x519B0FFE) /* SIGnature BUFFEr */

typedef struct BufferStruct {
  Sig sig;                      /* design.mps.sig */
  BufferClass class;            /* buffer class structure */
  Serial serial;                /* from pool->bufferSerial */
  Arena arena;                  /* owning arena */
  Pool pool;                    /* owning pool */
  RingStruct poolRing;          /* buffers are attached to pools */
  Bool isMutator;               /* TRUE iff buffer used by mutator */
  BufferMode mode;              /* Attached/Logged/Flipped/etc */
  double fillSize;              /* bytes filled in this buffer */
  double emptySize;             /* bytes emptied from this buffer */
  Addr base;                    /* base address of allocation buffer */
  Addr initAtFlip;              /* limit of initialized data at flip */
  APStruct apStruct;            /* the allocation point */
  Addr poolLimit;               /* the pool's idea of the limit */
  Align alignment;              /* allocation alignment */
  unsigned rampCount;           /* see impl.c.buffer.ramp.hack */
} BufferStruct;


/* SegBufStruct -- Buffer structure associated with segments
 *
 * .segbuf: SegBuf is a subclass of Buffer with support for attachment
 * to segments.  */

#define SegBufSig ((Sig)0x51959B0F) /* SIGnature SeG BUFfer  */

typedef struct SegBufStruct {
  BufferStruct bufferStruct;    /* superclass fields must come first */
  RankSet rankSet;              /* ranks of references being created */
  Seg seg;                      /* segment being buffered */
  Sig sig;                      /* design.mps.sig */
} SegBufStruct;


/* FormatStruct -- object format structure
 *
 * See design.mps.format-interface, impl.c.format.
 *
 * .single: In future, when more variants are added, FormatStruct should
 * really be replaced by a collection of format classes.  */

#define FormatSig       ((Sig)0x519F63A2) /* Signature FoRMAT */

typedef struct FormatStruct {
  Sig sig;
  Serial serial;                /* from arena->formatSerial */
  FormatVariety variety;        /* format variety (e.g. A) */
  Arena arena;                  /* owning arena */
  RingStruct arenaRing;         /* formats are attached to the arena */
  Align alignment;              /* alignment of formatted objects */
  FormatScanMethod scan;
  FormatSkipMethod skip;
  FormatMoveMethod move;
  FormatIsMovedMethod isMoved;
  FormatCopyMethod copy;
  FormatPadMethod pad;
  FormatClassMethod class;      /* pointer indicating class */
  Size headerSize;              /* size of header */
} FormatStruct;


/* LDStruct -- location dependency structure
 *
 * See design.mps.ld, and impl.c.ld.
 *
 * A version of this structure is exported to the client.  .ld.struct:
 * This must be kept in sync with impl.h.mps.ld.  See also
 * impl.c.mpsi.check.ld.  */

typedef struct LDStruct {
  Epoch epoch;          /* epoch when ld was last reset / init'ed */
  RefSet rs;            /* RefSet of Add'ed references */
} LDStruct;


/* ScanState
 *
 * .ss: See impl.c.trace.
 *
 * .ss: The first four fields of the trace structure must match the
 * external scan state structure (mps_ss_s) thus:
 *   ss->fix            mps_ss->fix
 *   ss->zoneShift      mps_ss->w0
 *   ss->white          mps_ss->w1
 *   ss->unfixedSummary mps_ss->w2
 *   ss->fixedSummary   mps_ss->w3
 * See impl.h.mps.ss and impl.c.mpsi.check.ss.  This is why the Sig
 * field is in the middle of this structure.  .ss.zone: The zoneShift
 * field is therefore declared as Word rather than Shift.  */

#define ScanStateSig    ((Sig)0x5195CA45) /* SIGnature SCAN State */

typedef struct ScanStateStruct {
  TraceFixMethod fix;           /* fix function */
  Word zoneShift;               /* copy of arena->zoneShift.  See .ss.zone */
  ZoneSet white;                /* white set, for inline fix test */
  RefSet unfixedSummary;        /* accumulated summary of scanned references */
  RefSet fixedSummary;          /* accumulated summary of fixed references */
  Sig sig;                      /* design.mps.sig */
  Arena arena;                  /* owning arena */
  Seg seg;                      /* segment being scanned */
  TraceSet traces;              /* traces to scan for */
  Rank rank;                    /* reference rank of scanning */
  Res res;                      /* current error state */
  STATISTIC_DECL(Count fixRefCount); /* refs which pass zone check */
  STATISTIC_DECL(Count segRefCount); /* refs which refer to segs */
  STATISTIC_DECL(Count whiteSegRefCount); /* refs which refer to white segs */
  STATISTIC_DECL(Count nailCount); /* segments nailed by ambig refs */
  STATISTIC_DECL(Count snapCount); /* refs snapped to forwarded objs */
  STATISTIC_DECL(Count forwardedCount); /* objects preserved by moving */
  Size forwardedSize;           /* bytes preserved by moving */
  STATISTIC_DECL(Count preservedInPlaceCount); /* objects preserved in place */
  Size preservedInPlaceSize;    /* bytes preserved in place */
  STATISTIC_DECL(Size copiedSize); /* bytes copied */
  STATISTIC_DECL(Size scannedSize); /* bytes scanned */
} ScanStateStruct;


/* TraceStruct -- tracer state structure */

#define TraceSig ((Sig)0x51924ACE) /* SIGnature TRACE */

typedef struct TraceStruct {
  Sig sig;                      /* design.mps.sig */
  TraceId ti;                   /* index into TraceSets */
  Arena arena;                  /* owning arena */
  ZoneSet white;                /* zones in the white set */
  ZoneSet mayMove;              /* zones containing possibly moving objs */
  TraceState state;             /* current state of trace */
  Rank rootRank;                /* next rank of roots to flip */
  Bool emergency;               /* ran out of memory during trace */
  Chain chain;                  /* chain being incrementally collected */
  Size condemned;               /* condemned bytes */
  Size notCondemned;            /* collectable but not condemned */
  Size foundation;              /* initial grey set size */
  Size rate;                    /* segs to scan per increment */
  STATISTIC_DECL(Count greySegCount); /* number of grey segs */
  STATISTIC_DECL(Count greySegMax); /* max number of grey segs */
  STATISTIC_DECL(Count rootScanCount); /* number of roots scanned */
  STATISTIC_DECL(Count rootScanSize); /* total size of scanned roots */
  STATISTIC_DECL(Size rootCopiedSize); /* bytes copied by scanning roots */
  STATISTIC_DECL(Count segScanCount); /* number of segs scanned */
  Count segScanSize;            /* total size of scanned segments */
  STATISTIC_DECL(Size segCopiedSize); /* bytes copied by scanning segments */
  STATISTIC_DECL(Count singleScanCount); /* number of single refs scanned */
  STATISTIC_DECL(Count singleScanSize); /* total size of single refs scanned */
  STATISTIC_DECL(Size singleCopiedSize); /* bytes copied by scanning single refs */
  STATISTIC_DECL(Count fixRefCount); /* refs which pass zone check */
  STATISTIC_DECL(Count segRefCount); /* refs which refer to segs */
  STATISTIC_DECL(Count whiteSegRefCount); /* refs which refer to white segs */
  STATISTIC_DECL(Count nailCount); /* segments nailed by ambig refs */
  STATISTIC_DECL(Count snapCount); /* refs snapped to forwarded objs */
  STATISTIC_DECL(Count readBarrierHitCount); /* read barrier faults */
  STATISTIC_DECL(Count pointlessScanCount); /* pointless seg scans */
  STATISTIC_DECL(Count forwardedCount); /* objects preserved by moving */
  Size forwardedSize;           /* bytes preserved by moving */
  STATISTIC_DECL(Count preservedInPlaceCount); /* objects preserved in place */
  Size preservedInPlaceSize;    /* bytes preserved in place */
  STATISTIC_DECL(Count reclaimCount); /* segments reclaimed */
  STATISTIC_DECL(Count reclaimSize); /* bytes reclaimed */
} TraceStruct;


/* ChunkCacheEntryStruct -- cache entry in the chunk cache */

#define ChunkCacheEntrySig ((Sig)0x519C80CE) /* SIGnature CHUnk Cache Entry */

typedef struct ChunkCacheEntryStruct {
  Sig sig;
  Chunk chunk;
  Addr base;
  Addr limit;
  Page pageTableBase;
  Page pageTableLimit;
} ChunkCacheEntryStruct;


/* ArenaClassStruct -- generic arena class interface */

#define ArenaClassSig   ((Sig)0x519A6C1A) /* SIGnature ARena CLAss */

typedef struct ArenaClassStruct {
  ProtocolClassStruct protocol;
  char *name;                   /* class name string */
  size_t size;                  /* size of outer structure */
  size_t offset;                /* offset of generic struct in outer struct */
  ArenaInitMethod init;
  ArenaFinishMethod finish;
  ArenaReservedMethod reserved;
  ArenaSpareCommitExceededMethod spareCommitExceeded;
  ArenaExtendMethod extend;
  ArenaAllocMethod alloc;
  ArenaFreeMethod free;
  ArenaChunkInitMethod chunkInit;
  ArenaChunkFinishMethod chunkFinish;
  ArenaDescribeMethod describe;
  Sig sig;
} ArenaClassStruct;


/* GlobalsStruct -- the global state associated with an arena
 *
 * .space: The arena structure holds the entire state of the MPS, and as
 * such contains a lot of fields which are considered "global".  These
 * fields belong to different modules.  The module which owns each group
 * of fields is commented.  */

#define GlobalsSig ((Sig)0x519970BA) /* SIGnature GLOBAls */

typedef struct GlobalsStruct {
  Sig sig;

  /* general fields (impl.c.global) */
  RingStruct globalRing;        /* node in global ring of arenas */
  Lock lock;                    /* arena's lock */

  /* polling fields (impl.c.global) */
  double pollThreshold;         /* design.mps.arena.poll */
  Bool insidePoll;
  Bool clamped;                 /* prevent background activity */
  double fillMutatorSize;       /* total bytes filled, mutator buffers */
  double emptyMutatorSize;      /* total bytes emptied, mutator buffers */
  double allocMutatorSize;      /* fill-empty, only asymptotically accurate */
  double fillInternalSize;      /* total bytes filled, internal buffers */
  double emptyInternalSize;     /* total bytes emptied, internal buffers */

  /* version field (impl.c.version) */
  const char *mpsVersionString; /* MPSVersion() */

  /* buffer fields (impl.c.buffer) */
  Bool bufferLogging;           /* design.mps.buffer.logging.control */

  /* pool fields (impl.c.pool) */
  RingStruct poolRing;          /* ring of pools in arena */
  Serial poolSerial;            /* serial of next created pool */

  /* root fields (impl.c.root) */
  RingStruct rootRing;          /* ring of roots attached to arena */
  Serial rootSerial;            /* serial of next root */
} GlobalsStruct;


/* ArenaStruct -- generic arena
 *
 * See impl.c.arena.  */

#define ArenaSig        ((Sig)0x519A6E4A) /* SIGnature ARENA */

typedef struct ArenaStruct {
  GlobalsStruct globals; /* must be first, see design.mps.arena.globals */
  Serial serial;

  ArenaClass class;             /* arena class structure */

  Bool poolReady;               /* design.mps.arena.pool.ready */
  MVStruct controlPoolStruct;   /* design.mps.arena.pool */

  ReservoirStruct reservoirStruct; /* design.mps.reservoir */

  Size committed;               /* amount of committed RAM */
  Size committedMax;            /* max value of committed so far */
  Size commitLimit;             /* client-configurable commit limit */

  Size spareCommitted;          /* Amount of memory in hysteresis fund */
  Size spareCommitLimit;        /* Limit on spareCommitted */

  Shift zoneShift;              /* see also impl.c.ref */
  Align alignment;              /* minimum alignment of tracts */

  Tract lastTract;              /* most recently allocated tract */
  Addr lastTractBase;           /* base address of lastTract */

  Chunk primary;                /* the primary chunk */
  RingStruct chunkRing;         /* all the chunks */
  Serial chunkSerial;           /* next chunk number */
  ChunkCacheEntryStruct chunkCache; /* just one entry */

  /* locus fields (impl.c.locus) */
  GenDescStruct topGen;         /* generation descriptor for dynamic gen */

  /* format fields (impl.c.format) */
  RingStruct formatRing;        /* ring of formats attached to arena */
  Serial formatSerial;          /* serial of next format */

  /* message fields (design.mps.message, impl.c.message) */
  RingStruct messageRing;       /* ring of pending messages */
  BT enabledMessageTypes;       /* map of which types are enabled */

  /* finalization fields (design.mps.finalize), impl.c.poolmrg */
  Bool isFinalPool;             /* indicator for finalPool */
  Pool finalPool;               /* either NULL or an MRG pool */

  /* thread fields (impl.c.thread) */
  RingStruct threadRing;        /* ring of attached threads */
  Serial threadSerial;          /* serial of next thread */

  /* shield fields (impl.c.shield) */
  Bool insideShield;             /* TRUE if and only if inside shield */
  Seg shCache[ShieldCacheSIZE];  /* Cache of unsynced segs */
  Size shCacheI;                 /* index into cache */
  Size shCacheLimit;             /* High water mark for cache usage */
  Size shDepth;                  /* sum of depths of all segs */
  Bool suspended;                /* TRUE iff mutator suspended */

  /* trace fields (impl.c.trace) */
  TraceSet busyTraces;          /* set of running traces */
  TraceSet flippedTraces;       /* set of running and flipped traces */
  TraceStruct trace[TraceLIMIT]; /* trace structures.  See
                                   design.mps.trace.intance.limit */
  RingStruct greyRing[RankLIMIT]; /* ring of grey segments at each rank */
  STATISTIC_DECL(Count writeBarrierHitCount); /* write barrier hits */
  RingStruct chainRing;         /* ring of chains */

  /* location dependency fields (impl.c.ld) */
  Epoch epoch;                     /* design.mps.arena.ld.epoch */
  RefSet prehistory;               /* design.mps.arena.ld.prehistory */
  RefSet history[LDHistoryLENGTH]; /* design.mps.arena.ld.history */

  Sig sig;
} ArenaStruct;


typedef struct AllocPatternStruct {
  char dummy;
} AllocPatternStruct;


#endif /* mpmst_h */
