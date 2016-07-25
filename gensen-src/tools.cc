// 
// tools.cc      : Implements a few utility functions
// authors       : Fabio Silva
//
// Copyright (C) 2000-2002 by the University of Southern California
// $Id: tools.cc,v 1.1 2005/04/22 06:08:37 fstann Exp $
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

#include "tools.hh"

void GetTime(struct timeval *tv)
{
  gettimeofday(tv, NULL);
}

void SetSeed(struct timeval *tv) 
{
  srand(tv->tv_usec);
}

int GetRand()
{
  return (rand());
}
