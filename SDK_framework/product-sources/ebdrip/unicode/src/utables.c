/** \file
 * \ingroup unicode
 *
 * $HopeName: HQNc-unicode!src:utables.c(EBDSDK_P.1) $
 *
 * Copyright (C) 2004-2007 Global Graphics Software Ltd. All rights reserved.
 * Global Graphics Software Ltd. Confidential Information.
 *
 * \brief
 * Unicode manipulation data tables
 *
 * The Unicode manipulation functions provide rudimentary facilities to convert
 * between Unicode transformation representations, to compare normalised Unicode
 * sequences, and to iterate over Unicode sequences. These tables assist in
 * parsing UTF-8 sequences.
 */

#include "hqunicode.h"
#include "uprivate.h"

/** \brief Length table for UTF-8 conversion

    Table indexed by a start byte, yielding the number of bytes in the UTF-8
    encoding it introduces. Zero indicates an invalid UTF-8 start byte.
 */
uint8 utf8_length[256] = {
   0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1, /* 0 */
   0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,
   0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1, /* 0x10 */
   0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,
   0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1, /* 0x20 */
   0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,
   0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1, /* 0x30 */
   0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,
   0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1, /* 0x40 */
   0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,
   0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1, /* 0x50 */
   0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,
   0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1, /* 0x60 */
   0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,
   0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1, /* 0x70 */
   0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1,
   0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0, /* 0x80 */
   0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
   0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0, /* 0x90 */
   0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
   0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0, /* 0xa0 */
   0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
   0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0, /* 0xb0 */
   0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
   0x0,  0x0,  0x2,  0x2,  0x2,  0x2,  0x2,  0x2, /* 0xc0 */
   0x2,  0x2,  0x2,  0x2,  0x2,  0x2,  0x2,  0x2,
   0x2,  0x2,  0x2,  0x2,  0x2,  0x2,  0x2,  0x2, /* 0xd0 */
   0x2,  0x2,  0x2,  0x2,  0x2,  0x2,  0x2,  0x2,
   0x3,  0x3,  0x3,  0x3,  0x3,  0x3,  0x3,  0x3, /* 0xe0 */
   0x3,  0x3,  0x3,  0x3,  0x3,  0x3,  0x3,  0x3,
   0x4,  0x4,  0x4,  0x4,  0x4,  0x0,  0x0,  0x0, /* 0xf0 */
   0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0
} ;

/** \brief Minimum value table for UTF-8 conversion

    This is used to check the valid ranges for UTF-8 representations, to
    ensure the "shortest encoding" condition is met. Note that the Unicode
    4.0 standard does not phrase the UTF-8 requirement as "shortest encoding"
    anymore, but the syntax it provides performs the same function. This
    library simplifies the parsing by reading all forms, and then checking the
    validity. This table is indexed by the number of bytes in the UTF-8
    representation.
 */
UTF32 utf8_minimum[5] = {
  0,       /* invalid representation */
  0,       /* one byte: 0x0-0x7f */
  0x80,    /* two bytes: 0x80-0x7ff */
  0x800,   /* three bytes: 0x800-0xffff */
  0x10000  /* four bytes: 0x10000-0x10ffff */
} ;

/** \brief Mask table for UTF-8 conversion

    Masks to remove the unwanted bits from the start byte of UTF-8
    representations. This table is indexed by the number of bytes in the UTF-8
    representation.
 */
UTF8 utf8_mask[5] = {
  0,    /* invalid representation */
  0x7f, /* one byte: ~0xxxxxxx */
  0x1f, /* two bytes: ~110xxxxx */
  0x0f, /* three bytes: ~1110xxxx */
  0x07  /* four bytes: ~11110xxx */
} ;

/** \brief Mark table for UTF-8 conversion

    Values ORed into first byte to indicate the number of bytes in a UTF-8
    code point.
 */
UTF8 utf8_marker[5] = {
  0,    /* invalid representation */
  0x0,  /* one byte: 0xxxxxxx */
  0xc0, /* two bytes: 110xxxxx */
  0xe0, /* three bytes: 1110xxxx */
  0xf0  /* four bytes: 11110xxx */
} ;

/*
Log stripped */