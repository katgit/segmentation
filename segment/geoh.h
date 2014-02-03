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

#ifndef	GEO_H
#define	GEO_H

/*
 * geodetic header
 */

typedef struct {
	double          bline;		/* begin line #			 */
	double          bsamp;		/* begin sample #		 */
	double          dline;		/* line increment		 */
	double          dsamp;		/* sample increment		 */
	char           *units;		/* units of measurement		 */
	char           *csys;		/* coord system ID		 */
} GEOH_T;

#define	GEOH_HNAME	"geo"		/* header name within IPW	 */
#define	GEOH_VERSION	"$Revision: 1.8 $"	/* RCS revsion #	 */

/* field keywords */
#define	GEOH_BLINE	"bline"
#define	GEOH_BSAMP	"bsamp"
#define	GEOH_DLINE	"dline"
#define	GEOH_DSAMP	"dsamp"
#define	GEOH_UNITS	"units"
#define	GEOH_CSYS	"coord_sys_ID"

/* field access macros */
#define	geoh_bline(p)	( (p)->bline )
#define	geoh_bsamp(p)	( (p)->bsamp )
#define	geoh_dline(p)	( (p)->dline )
#define	geoh_dsamp(p)	( (p)->dsamp )
#define	geoh_units(p)	( (p)->units )
#define	geoh_csys(p)	( (p)->csys )

/* coordinate conversion macros */
#define	GEO_LINE(p, L)	( ((L) * (p)->dline) + (p)->bline )
#define	GEO_SAMP(p, s)	( ((s) * (p)->dsamp) + (p)->bsamp )

/* function declarations */
extern bool_t   geohcheck();
extern GEOH_T **geohdup();
extern GEOH_T  *geohmake();
extern GEOH_T **geohread();
extern int      geohwrite();
extern double	geohspace();

/* $Header: /local/share/pkg/ipw/h/RCS/geoh.h,v 1.8 90/11/11 16:59:32 frew Exp $ */
#endif
