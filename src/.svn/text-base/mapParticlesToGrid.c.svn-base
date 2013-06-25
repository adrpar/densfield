// Copyright (C) 2010, Steffen Knollmann
// Released under the terms of the GNU General Public License version 3.
// This file is part of `densfield'.


/*--- Includes ----------------------------------------------------------*/
#include "../config.h"
#include "mapParticlesToGrid.h"
#include "libadts/part.h"
#include <inttypes.h>
#ifdef WITH_OPENMP
#  include <omp.h>
#endif


/*--- Prototypes of local functions -------------------------------------*/
static void
local_getGridPosAndDist(grid_t   grid,
                        part_t   part,
                        uint32_t *gridPos,
                        double   *dist);

static uint32_t
local_getWeights(grid_t grid, part_t part, double *dist, double *weight);

static void
local_mapValues(part_t   part,
                grid_t   grid,
                double   *weights,
                uint32_t weightBaseSize,
                uint32_t *gridPos);

static void
local_setGridInformation(partBuffer_t pbuf, grid_t grid);


/*--- Implementations of exported functions -----------------------------*/
extern void
mapParticlesToGrid(partBuffer_t pbuf, grid_t grid)
{
	uint64_t numPartsAvailable;
	part_t   part;
	uint32_t weightBaseSize;
	uint32_t bunchCounter = UINT32_C(1);
#ifdef WITH_OPENMP
	double   timing;
#endif

#ifndef USE_FAKE_PARTICLES
	partBuffer_refillBuffer(pbuf);
#endif
	while ((numPartsAvailable = partBuffer_numPartsAvailable(pbuf)) > 0) {
		printf("Bunch %" PRIu32 " containing %" PRIu64 " particles...",
		       bunchCounter, numPartsAvailable);
		fflush(stdout);
#ifdef WITH_OPENMP
		timing = -omp_get_wtime();
#  pragma omp parallel for private(part, weightBaseSize) \
           schedule(guided)
#endif
		for (uint64_t i = 0; i < numPartsAvailable; i++) {
			uint32_t gridPos[NDIM];
			double   dist[NDIM];
			double   weight[POW_NDIM(MAXBASESIZE)];

			part           = partBuffer_getPartByIndex(pbuf, i);
			local_getGridPosAndDist(grid, part, gridPos, dist);
			weightBaseSize = local_getWeights(grid, part, dist, weight);
			local_mapValues(part, grid, weight, weightBaseSize, gridPos);
		}
#ifdef WITH_OPENMP
		timing += omp_get_wtime();
		printf(" done (%fs)\n", timing);
#else
		printf(" done\n");
#endif
		bunchCounter++;
		partBuffer_refillBuffer(pbuf);
	}
	local_setGridInformation(pbuf, grid);
} /* mapParticlesToGrid */

/*--- Implementations of local functions --------------------------------*/
static void
local_getGridPosAndDist(grid_t   grid,
                        part_t   part,
                        uint32_t *gridPos,
                        double   *dist)
{
	fpv_t  *realPos;
	double realGridPos[NDIM];

	realPos = part_getRealPos(part);
	grid_convertRealPosToRealGridPos(grid, realPos, realGridPos);
	grid_convertRealGridPosToGridPos(realGridPos, gridPos);
	grid_calcDistToCellCenter(realGridPos, dist);
}

static uint32_t
local_getWeights(grid_t grid, part_t part, double *dist, double *weight)
{
	uint32_t weightBaseSize;
#ifdef WITH_MAPPING_SPH
	fpv_t    hsml;
#endif

	if (part_isSPHParticle(part)) {
#ifdef WITH_MAPPING_SPH
		hsml           = part_getHsml(part);
		weightBaseSize = grid_getWeightsSPH(grid, hsml, dist, weight);
#else
#  ifndef WITH_MAPPING_CIC
		weightBaseSize = grid_getWeightsTSC(dist, weight);
#  else
		weightBaseSize = grid_getWeightsCIC(dist, weight);
#  endif
#endif
	} else {
		weightBaseSize = grid_getWeightsTSC(dist, weight);
	}
	return weightBaseSize;
}

static void
local_mapValues(part_t   part,
                grid_t   grid,
                double   *weights,
                uint32_t weightBaseSize,
                uint32_t *gridPos)
{
	fpv_t    mass, vel, u;
	uint32_t affectedCells[POW_NDIM(MAXBASESIZE)];

	grid_getAffectedCells(grid, gridPos, weightBaseSize, affectedCells);

	mass = part_getMass(part);
	grid_mapValueToVarByIndex(grid, 0, mass, weights,
	                          weightBaseSize, affectedCells);
	for (int i = 0; i < NDIM; i++) {
		vel = part_getVel(part, i);
		grid_mapValueToVarByIndex(grid, 1 + i, mass * vel, weights,
		                          weightBaseSize, affectedCells);
	}
	if (part_isSPHParticle(part)) {
		grid_mapValueToVarByIndex(grid, 4, mass, weights,
		                          weightBaseSize, affectedCells);
		u = part_getU(part);
		grid_mapValueToVarByIndex(grid, 5, u * mass, weights,
		                          weightBaseSize, affectedCells);
	}
}

static void
local_setGridInformation(partBuffer_t pbuf, grid_t grid)
{
	double tmp;
	tmp = partBuffer_getBoxsize(pbuf);
	grid_setBoxsize(grid, tmp);
	tmp = partBuffer_getExpansion(pbuf);
	grid_setTimeIndex(grid, tmp);
}
