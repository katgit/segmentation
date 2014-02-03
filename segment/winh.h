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

#ifndef	WIN_H
#define	WIN_H

/*
 * window header
 */

typedef struct {
	double          bline;		/* begin line #			 */
	double          bsamp;		/* begin sample #		 */
	double          dline;		/* line increment		 */
	double          dsamp;		/* sample increment		 */
} WINH_T;

#define	WINH_HNAME	"win"		/* header name within IPW	 */
#define	WINH_VERSION	"$Revision: 1.8 $"	/* RCS revsion #	 */

/* field keywords */
#define	WINH_BLINE	"bline"
#define	WINH_BSAMP	"bsamp"
#define	WINH_DLINE	"dline"
#define	WINH_DSAMP	"dsamp"

/* field access macros */
#define	winh_bline(p)	( (p)->bline )
#define	winh_bsamp(p)	( (p)->bsamp )
#define	winh_dline(p)	( (p)->dline )
#define	winh_dsamp(p)	( (p)->dsamp )

/* coordinate conversion macros */
#define	WIN_LINE(p, L)	( ((L) * (p)->dline) + (p)->bline )
#define	WIN_SAMP(p, s)	( ((s) * (p)->dsamp) + (p)->bsamp )

/* function declarations */
extern bool_t   winhcheck();
extern WINH_T **winhdup();
extern WINH_T  *winhmake();
extern WINH_T **winhread();
extern int      winhwrite();

/* $Header: /local/share/pkg/ipw/h/RCS/winh.h,v 1.8 90/11/11 17:00:22 frew Exp $ */
#endif
