// Copyright (C) 2010, Steffen Knollmann
// Released under the terms of the GNU General Public License version 3.
// This file is part of `densfield'.


#ifndef MAPPARTICLESTOGRID_H
#define MAPPARTICLESTOGRID_H


/*--- Includes ----------------------------------------------------------*/
#include "../config.h"
#include "libadts/grid.h"
#include "libadts/partBuffer.h"


/*--- Prototypes of exported functions ----------------------------------*/
extern void
mapParticlesToGrid(partBuffer_t pbuf, grid_t grid);


#endif
