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

#ifndef	SAT_H
#define	SAT_H

/*
** NAME
**	sath.h -- header file for SATH header
**
** SYNOPSIS
**	#include "sath.h"
**
** DESCRIPTION
**
** FUTURE DIRECTIONS
**
** BUGS
*/

typedef struct {
	char           *platform;	/* e.g. "Landsat", "ER2", ...	*/
	char           *sensor;		/* e.g. "TM", "AVIRIS", ... 	*/
	char           *location;	/* e.g. Landsat path,row,quad	*/
	char           *gmdate;		/* YYYYMMDD		 	*/
	char           *gmtime;		/* hhmmss.sss...	 	*/
} SATH_T;

#define	SATH_HNAME	"sat"		/* header name within IPW	 */
#define	SATH_VERSION	"$Revision: 1.2 $"	/* RCS revsion #	 */

/* field keywords */
#define	SATH_PLATFORM		"platform"
#define	SATH_SENSOR		"sensor"
#define	SATH_LOCATION		"location"
#define	SATH_GMDATE		"gmdate"
#define	SATH_GMTIME		"gmtime"

/* field access macros */
#define	sath_platform(p)	( (p)->platform )
#define	sath_sensor(p)	( (p)->sensor )
#define	sath_location(p) ( (p)->location )
#define	sath_gmdate(p)	( (p)->gmdate )
#define	sath_gmtime(p)	( (p)->gmtime )

/* function declarations */
extern bool_t   sathcheck();
extern SATH_T  **sathdup();
extern SATH_T   *sathmake();
extern SATH_T  **sathread();
extern int      sathwrite();

/* $Header: /local/share/pkg/ipw/h/RCS/sath.h,v 1.2 90/11/11 17:00:13 frew Exp $ */
#endif
