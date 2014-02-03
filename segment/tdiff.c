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

/* LINTLIBRARY */

#include <time.h>
#include "ipw.h"

/*
** NAME
**	tdiff -- time difference between two time structures
**
** SYNOPSIS
**	#include <time.h>
**
**	long tdiff(t2, t1)
**	struct tm *t1, *t2;
**
** DESCRIPTION
**	Tdiff returns the difference in seconds between t2 and t1.
**
** RETURN VALUE
**	Result.
**
** ERRORS
**	Dies on error.
*/

#define SEC_DAY	86400
#define SEC_HR	3600
#define SEC_MIN	60

long
tdiff(t2, t1)
	struct tm      *t2;
	struct tm      *t1;
{
	long            seconds;

 /*
  * difference between midnight times
  */
	seconds = SEC_DAY *
		(julday(1900 + t2->tm_year, 1 + t2->tm_mon, t2->tm_mday)
	   - julday(1900 + t1->tm_year, 1 + t1->tm_mon, t1->tm_mday));
 /*
  * adjust for times of day
  */
	seconds -= t1->tm_hour * SEC_HR + t1->tm_min * SEC_MIN + t1->tm_sec;
	seconds += t2->tm_hour * SEC_HR + t2->tm_min * SEC_MIN + t2->tm_sec;

	return (seconds);
}

#ifndef	lint
static char     rcsid[] = "$Header: /share1/ipw-1.1/share/src/lib/libipw/util/RCS/tdiff.c,v 1.3 1997/02/17 04:27:40 ceretha Exp $";

#endif
