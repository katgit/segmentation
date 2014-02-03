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

#ifndef	LQH_H
#define	LQH_H

/*
** NAME
**	lqh.h -- header file for LQH header
**
** SYNOPSIS
**	#include "lqh.h"
**
** DESCRIPTION
**
** FUTURE DIRECTIONS
**
** BUGS
*/

typedef struct {
	int            *bkpt;		/* breakpoint array		 */
	fpixel_t       *map;		/* LQ = map[pixel]		 */
	char           *units;		/* units of measure		 */
	char           *interp;		/* interpolation function name	 */
 /*
  * stuff below here is derived, not read from header
  */
	int             nbkpts;		/* # breakpoints		 */
	int             maplen;		/* # elements / map array	 */
	bool_t          mapped;		/* ? map has been interpolated	 */
	fpixel_t       *lininv;		/* linear inverse map coefs.	 */
} LQH_T;

#define	LQH_HNAME	"lq"		/* header name within IPW	 */
#define	LQH_VERSION	"$Revision: 1.5 $"	/* RCS revsion #	 */

/* field keywords */
#define	LQH_MAP		"map"
#define	LQH_UNITS	"units"
#define	LQH_INTERP	"interp"

/* field access macros */
#define	lqh_bkpt(p)	( (p)->bkpt )
#define	lqh_map(p)	( (p)->map )
#define	lqh_units(p)	( (p)->units )
#define	lqh_interp(p)	( (p)->interp )
#define	lqh_nbkpts(p)	( (p)->nbkpts )
#define	lqh_maplen(p)	( (p)->maplen )
#define	lqh_mapped(p)	( (p)->mapped )
#define	lqh_lininv(p)	( (p)->lininv )

/* "iname" values */
#define	LQH_LIN_INTERP	"linear"

/* function declarations */
extern LQH_T  **lqh();
extern bool_t   lqhcheck();
extern LQH_T  **lqhdup();
extern int      lqhinterp();
extern LQH_T   *lqhmake();
extern LQH_T  **lqhread();
extern int      lqhwrite();

/* $Header: /local/share/pkg/ipw/h/RCS/lqh.h,v 1.5 90/11/11 16:59:45 frew Exp $ */
#endif
