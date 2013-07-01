// Copyright (C) 2010, Steffen Knollmann, Adrian M. Partl
// Released under the terms of the GNU General Public License version 3.
// This file is part of `densfield'.


/*--- Includes ----------------------------------------------------------*/
#include "../config.h"
#include "normalizeGrids.h"
#include <inttypes.h>
#ifdef WITH_OPENMP
#  include <omp.h>
#endif
#include <stdio.h>


/*--- Prototypes of local functions -------------------------------------*/


/*--- Implementations of exported functions -----------------------------*/
extern void
normalizeGrids(grid_t grid)
{
	long double totalMass;
	long double totalGasMass;
	long double normDens;
	long double normGasDens;
#ifdef WITH_OPENMP
	double      timing;
#endif

	printf("Starting to scale the  grids:  \n");
	fflush(NULL);
	normGasDens  = normDens = (long double)grid_getNumCellsTotal(grid);
	totalMass    = grid_sumupAllValuesOnVariableByNum(grid, 0);
	normDens    /= totalMass;
	totalGasMass = grid_sumupAllValuesOnVariableByNum(grid, 4);
	normGasDens /= totalGasMass;
	printf("Total mass = %Lf\tnormDens = %Lf\n", totalMass, normDens);
	printf("Total gas mass = %Lf\tnormGasDens = %Lf\n",
	       totalGasMass, normGasDens);
#ifdef WITH_OPENMP
	timing = -omp_get_wtime();
#endif
	grid_divideVariablesByNum(grid, 1, 0);
	grid_divideVariablesByNum(grid, 2, 0);
	grid_divideVariablesByNum(grid, 3, 0);
#ifdef WITH_OPENMP
	timing += omp_get_wtime();
	printf("\tvelocity done (%fs)\n", timing);
	timing  = -omp_get_wtime();
#else
	printf("\tvelocity done\n");
#endif
	grid_scaleVariablesByNum(grid, 0, normDens);
#ifdef WITH_OPENMP
	timing += omp_get_wtime();
	printf("\tdensity done (%fs)\n", timing);
	timing  = -omp_get_wtime();
#else
	printf("\tdensity done\n");
#endif
	grid_divideVariablesByNum(grid, 5, 4);      //u / mass
	grid_scaleVariablesByNum(grid, 4, normGasDens);
#ifdef WITH_OPENMP
	timing += omp_get_wtime();
	printf("\tgas density done (%fs)\n", timing);
#else
	printf("\tgas density done\n");
#endif
} /* normalizeGrids */

/*--- Implementations of local functions --------------------------------*/
