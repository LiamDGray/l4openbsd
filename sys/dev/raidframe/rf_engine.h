/*	$OpenBSD: rf_engine.h,v 1.4 2002/12/16 07:01:03 tdeval Exp $	*/
/*	$NetBSD: rf_engine.h,v 1.3 1999/02/05 00:06:11 oster Exp $	*/

/*
 * Copyright (c) 1995 Carnegie-Mellon University.
 * All rights reserved.
 *
 * Author: William V. Courtright II, Mark Holland, Jim Zelenka
 *
 * Permission to use, copy, modify and distribute this software and
 * its documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 *
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND
 * FOR ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 *
 * Carnegie Mellon requests users of this software to return to
 *
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 *
 * any improvements or extensions that they make and grant Carnegie the
 * rights to redistribute these changes.
 */

/***********************************************************
 *                                                         *
 * engine.h -- Header file for execution engine functions. *
 *                                                         *
 ***********************************************************/

#ifndef	_RF__RF_ENGINE_H_
#define	_RF__RF_ENGINE_H_

extern void **rf_hook_cookies;

int  rf_ConfigureEngine(RF_ShutdownList_t **, RF_Raid_t *, RF_Config_t *);

	/* Return finished node to engine. */
int  rf_FinishNode(RF_DagNode_t *, int);

	/* Execute dag. */
int  rf_DispatchDAG(RF_DagHeader_t *, void (*) (void *), void *);

#endif	/* !_RF__RF_ENGINE_H_ */
