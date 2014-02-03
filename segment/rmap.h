/*
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that: (1) source distributions retain this entire copyright
 * notice and comment, and (2) distributions including binaries display
 * the following acknowledgement:  ``This product includes software
 * developed by the Computer Systems Laboratory, University of
 * California, Santa Barbara and its contributors'' in the documentation
 * or other materials provided with the distribution and in all
 * advertising materials mentioning features or use of this software.
 *
 * Neither the name of the University nor the names of its contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

#ifndef RMAP_H
#define RMAP_H

/*
 * resamp map range and special values:
 *
 * RMAP_FBITS	number of fraction bits per band in resamp map
 *
 * RMAP_IBITS	number of integer bits per band in resamp map (not including
 *		the sign bit)
 *
 * RMAP_QUANT	quantization limit of the resampling map (i.e., there is
 *		1/RMAP_QUANT of a {line,sample} accuracy available)
 *
 * RMAP_MIN	minimum location value that can be stored in resample map band:
 *			 ((-1)*(2^RMAP_IBITS - 1) + (1 - 2/RMAP_FBITS))
 *
 *		Note:	Using 2/RMAP_FBITS here so that the lowest value
 *			is reserved for the RMAP_BOGUS psuedo-value
 *
 * RMAP_MAX	maximum location value that can be stored in resample map band:
 *			((2^RMAP_IBITS - 1) + (1 - 1/RMAP_FBITS))
 *
 * RMAP_BOGUS	psuedo-value--acts as a flag to the ipw program resamp
 *		that indicates that the actual value was out of the
 *		range of the resampling map.
 */

#define	RMAP_FBITS	5

#define	RMAP_IBITS	( (sizeof(pixel_t) * CHAR_BIT) - RMAP_FBITS )
#define	RMAP_QUANT	bit(RMAP_FBITS)

#if (RMAP_IBITS + RMAP_FBITS > FLT_MANT_DIG)
typedef double  rmap_t;
#else
typedef float   rmap_t;
#endif

#define	MAP_MIN		0
#define	MAP_MAX		( (rmap_t) mask(RMAP_IBITS) +	\
			  ((rmap_t) (RMAP_QUANT - 1) /	\
			   (rmap_t) RMAP_QUANT) )

#define RMAP_BOGUS	(MAP_MAX + ((rmap_t) 1.0 / (rmap_t) RMAP_QUANT))

/* $Header: /local/share/pkg/ipw/h/RCS/rmap.h,v 1.6 90/11/11 17:00:11 frew Exp $ */
#endif
