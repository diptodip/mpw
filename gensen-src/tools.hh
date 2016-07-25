// 
// tools.hh      : Utility functions
// authors       : Fabio Silva
//
// Copyright (C) 2000-2002 by the University of Southern California
// $Id: tools.hh,v 1.1 2005/04/22 06:08:37 fstann Exp $
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License,
// version 2, as published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.
//
//

//
// This file contains OS abstractions to make it easy to use diffusion
// in different environments (i.e. in simulations, where time is
// virtualized, and in embeddedd apps where error logging happens in
// some non-trivial way).

#ifndef _TOOLS_HH_
#define _TOOLS_HH_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif // HAVE_CONFIG_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

// SetSeed sets the random number generator's seed with the timeval
// structure given in tv (which is not changed)
void SetSeed(struct timeval *tv);

// GetTime returns a timeval structure with the current system time
void GetTime(struct timeval *tv);

// GetRand returns a random number between 0 and RAND_MAX
int GetRand();

#endif // !_TOOLS_HH_
