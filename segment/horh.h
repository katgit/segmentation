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

#ifndef	HOR_H
#define	HOR_H

/*
 * horizon header
 */

typedef struct {
	double          azimuth;	/* direction toward horizons	 */
} HORH_T;

#define	HORH_HNAME	"hor"		/* header name within IPW	 */
#define	HORH_VERSION	"$Revision: 1.3 $"	/* RCS revsion #	 */

/* field keywords */
#define	HORH_AZM	"azimuth"

/* field access macros */
#define	horh_azm(p)	( (p)->azimuth )

/* function declarations */
extern HORH_T  *horhmake();
extern HORH_T **horhread();
extern int      horhwrite();
extern bool_t   horhcheck();

/* $Header: /local/share/pkg/ipw/h/RCS/horh.h,v 1.3 90/11/11 16:59:41 frew Exp $ */
#endif
