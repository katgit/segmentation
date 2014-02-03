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

#ifndef	OR_H
#define	OR_H

/*
 * orientation header
 */

typedef struct {
	char           *orient;		/* orientation			 */
	char           *origin;		/* corner of origin		 */
} ORH_T;

#define	ORH_HNAME	"or"		/* header name within IPW	 */
#define	ORH_VERSION	"$Revision: 1.4 $"	/* RCS revsion #	 */

/* field keywords */
#define	ORH_OR		"orientation"
#define	ORH_ORIGIN	"origin"

/* field access macros */
#define orh_orient(p)	( (p)->orient )
#define orh_origin(p)	( (p)->origin )

/* definitions */
#define ROW		"row-major"
#define COLUMN		"column-major"
#define ORIG_1		"upper left"
#define ORIG_2		"upper right"
#define ORIG_3		"lower right"
#define ORIG_4		"lower left"
#define IPW_ORIENT	ROW
#define IPW_ORIGIN	ORIG_1
#define XT_ORIENT	COLUMN

/* function declarations */
extern bool_t   orhcheck();
extern ORH_T  **orhdup();
extern ORH_T   *orhmake();
extern ORH_T  **orhread();
extern int      orhwrite();

/* $Header: /local/share/pkg/ipw/h/RCS/orh.h,v 1.4 90/11/11 16:59:50 frew Exp $ */
#endif
