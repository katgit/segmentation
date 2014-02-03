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

#ifndef	SKEWH_H
#define	SKEWH_H

/*
** NAME
**	skewh.h -- header file for SKEWH header
**
** SYNOPSIS
**	#include "skew.h"
**
** DESCRIPTION
**	The presence of as skew header indicates that an image has been skewed
**	horizontally by the skew program.  The skew angle in the header is
**	used by skew to undo the skewing.
**
** FUTURE DIRECTIONS
**
** BUGS
*/

typedef struct {
	double          angle;		/* skew angle (degrees)		 */
} SKEWH_T;

#define	SKEWH_HNAME	"skew"		/* header name within IPW	 */
#define	SKEWH_VERSION	"$Revision: 1.3 $"	/* RCS revsion #	 */

/* field keywords */
#define	SKEWH_ANGLE		"angle"

/* field access macros */
#define	skewh_angle(p)	( (p)->angle )

/* misc. */
#define	SKEW_MAX	45.0		/* maximum skew angle		 */
#define	SKEW_MIN	(-45.0)		/* minimum skew angle		 */

/* function declarations */
extern bool_t   skewhcheck();
extern SKEWH_T *skewhmake();
extern SKEWH_T **skewhread();
extern int      skewhwrite();

/* $Header: /local/share/pkg/ipw/h/RCS/skewh.h,v 1.3 90/11/11 17:00:16 frew Exp $ */
#endif
