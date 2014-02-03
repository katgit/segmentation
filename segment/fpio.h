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

#ifndef	FPIO_H
#define	FPIO_H

extern int      fpclose();
extern fpixel_t *fpfmax();
extern fpixel_t *fpfmin();
extern void     fphdrs();
extern fpixel_t **fpmap();
extern int     *fpmaplen();
extern int      fpvread();
extern int      fpvwrite();

/* $Header: /local/share/pkg/ipw/h/RCS/fpio.h,v 1.4 90/11/11 16:59:30 frew Exp $ */
#endif
