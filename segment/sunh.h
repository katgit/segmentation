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

#ifndef	SUNH_H
#define	SUNH_H

/*
** NAME
**	sunh -- sun geometry header
**
** SYNOPSIS
**	#include "sunh.h"
**
** DESCRIPTION
**
** FUTURE DIRECTIONS
**
** BUGS
*/

typedef struct {
	double          cos_sun;	/* cosine solar zenith ang	 */
	double          zen_sun;	/* solar zenith angle (radians)	 */
	double          azm_sun;	/* solar azimuth (rad from S)	 */
}               SUNH_T;

#define	SUNH_HNAME	"sun"		/* header name within IPW	 */
#define	SUNH_VERSION	"$Revision: 1.2 $"	/* RCS revsion #	 */

/* field keywords */
#define	SUNH_COS	"cos_sun"
#define	SUNH_ZEN	"zen_sun"
#define	SUNH_AZM	"azm_sun"

/* field access macros */
#define sunh_cos(p)	((p)->cos_sun)
#define sunh_zen(p)	((p)->zen_sun)
#define sunh_azm(p)	((p)->azm_sun)

/* function declarations */
extern bool_t   sunhcheck();
extern SUNH_T **sunhdup();
extern SUNH_T  *sunhmake();
extern SUNH_T **sunhread();
extern int      sunhwrite();

/* $Header: /local/share/pkg/ipw/h/RCS/sunh.h,v 1.2 90/11/11 17:00:18 frew Exp $ */
#endif
