// Copyright (C) 2010, Steffen Knollmann
// Released under the terms of the GNU General Public License version 3.
// This file is part of `densfield'.


/*--- Includes ----------------------------------------------------------*/
#include "../config.h"
#include "writeGrid.h"


/*--- Prototypes of local functions -------------------------------------*/


/*--- Implementations of exported functions -----------------------------*/
extern void
writeGrid(grid_t grid, const char *outPrefix)
{
	int numVariables = grid_getNumVariables(grid);
	for (int i=0; i<numVariables; i++) {
		grid_writeVarDataByIndex(grid, outPrefix, i);
		grid_writeBovForVarDataByIndex(grid, outPrefix, i);
	}
}


/*--- Implementations of local functions --------------------------------*/
