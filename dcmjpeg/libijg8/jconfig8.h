/*
 *
 *  Copyright (C) 1998-2024, OFFIS e.V.
 *  All rights reserved.  See COPYRIGHT file for details.
 *
 *  This software and supporting documentation were developed by
 *
 *    OFFIS e.V.
 *    R&D Division Health
 *    Escherweg 2
 *    D-26121 Oldenburg, Germany
 *
 *
 *  Module: dcmjpeg
 *
 *  Author: Marco Eichelberg
 *
 *  Purpose:
 *    this file derives the preprocessor symbols required to compile
 *    the IJG library from the central DCMTK configuration file osconfig.h
 *
 */

#include "dcmtk/config/osconfig.h"

/* We assume ANSI C and don't support DOS, 
 * so the following settings need not be tested 
 */
#define HAVE_PROTOTYPES 
#define HAVE_UNSIGNED_CHAR 
#define HAVE_UNSIGNED_SHORT 
#undef NEED_FAR_POINTERS
#undef INCOMPLETE_TYPES_BROKEN

/* the following settings are derived from osconfig.h */

#ifdef C_CHAR_UNSIGNED
#define CHAR_IS_UNSIGNED
#endif

#ifdef HAVE_SYS_TYPES_H
#define NEED_SYS_TYPES_H
#endif

/* must always be defined for our implementation */
#define NEED_SHORT_EXTERNAL_NAMES

#ifdef JPEG_INTERNALS

#ifdef C_RIGHTSHIFT_UNSIGNED
#define RIGHT_SHIFT_IS_UNSIGNED
#endif

#define INLINE C_INLINE

/* These are for configuring the JPEG memory manager. */
#undef DEFAULT_MAX_MEM
#undef NO_MKTEMP

/* We don't want to use getenv which is thread unsafe on some platforms */
#define NO_GETENV

#endif /* JPEG_INTERNALS */
