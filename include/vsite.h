/*
 * $Id$
 * 
 *                This source code is part of
 * 
 *                 G   R   O   M   A   C   S
 * 
 *          GROningen MAchine for Chemical Simulations
 * 
 *                        VERSION 3.2.0
 * Written by David van der Spoel, Erik Lindahl, Berk Hess, and others.
 * Copyright (c) 1991-2000, University of Groningen, The Netherlands.
 * Copyright (c) 2001-2004, The GROMACS development team,
 * check out http://www.gromacs.org for more information.

 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * If you want to redistribute modifications, please consider that
 * scientific software is very special. Version control is crucial -
 * bugs must be traceable. We will be happy to consider code for
 * inclusion in the official distribution, but derived work must not
 * be called official GROMACS. Details are found in the README & COPYING
 * files - if they are missing, get the official version at www.gromacs.org.
 * 
 * To help us fund GROMACS development, we humbly ask that you cite
 * the papers on the package - you can find them in the top README file.
 * 
 * For more info, check our website at http://www.gromacs.org
 * 
 * And Hey:
 * Gromacs Runs On Most of All Computer Systems
 */

#ifndef _vsite_h
#define _vsite_h

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include "typedefs.h"

typedef struct {
  int nprevvsite; /* how many virtual sites are nonlocal */     
  int nnextvsite;
  int *idxprevvsite; /* index of nonlocal vsite particles */
  int *idxnextvsite;
  int nprevconstr; /* how many constr. atoms are nonlocal */
  int nnextconstr;
  int *idxprevconstr; /* indices of nonlocal constructing atoms */
  int *idxnextconstr;
} t_comm_vsites;

typedef struct {
  int  n_vsite;             /* The number of virtual sites             */
  int  n_intercg_vsite;     /* The number of inter charge group vsites */
  int  *vsite_pbc;          /* The pbc atoms for intercg vsites        */
  int  *vsite_pbc_dd;       /* The pbc atoms with DD                   */
  int  vsite_pbc_dd_nalloc;
  bool bPDvsitecomm;        /* Do we need vsite communication with PD? */
  t_comm_vsites *vsitecomm; /* The PD vsite communication struct       */
} gmx_vsite_t;

extern void construct_vsites(FILE *log,gmx_vsite_t *vsite,
			     rvec x[],t_nrnb *nrnb,
			     real dt,rvec v[],t_idef *idef,
			     int ePBC,bool bMolPBC,t_graph *graph,
			     t_commrec *cr,matrix box);
/* Create positions of vsite atoms based on surrounding atoms.
 */
 
extern void spread_vsite_f(FILE *log,gmx_vsite_t *vsite,
			   rvec x[],rvec f[],rvec *fshift,
			   t_nrnb *nrnb,t_idef *idef,
			   int ePBC,bool bMolPBC,t_graph *g,matrix box,
			   t_commrec *cr);
/* Spread the force operating on the vsite atoms on the surrounding atoms.
 * If fshift!=NULL also update the shift forces.
 */

extern gmx_vsite_t *init_vsite(t_commrec *cr,t_topology *top);
/* Initialize the virtual site struct,
 * returns NULL when there are no virtual sites.
 */

#endif

