// Copyright (C) 2010, Steffen Knollmann
// Released under the terms of the GNU General Public License version 3.
// This file is part of `densfield'.


/*--- Includes ----------------------------------------------------------*/
#include "../../config.h"
#include "grid.h"
#include "../libutil/xmem.h"
#include "../libutil/xfile.h"
#include "../libutil/xstring.h"
#include "../libutil/test_endian.h"
#include "../libutil/pow.h"
#include "../libutil/ndim_array_access.h"
#include <inttypes.h>
#include <string.h>
#include <math.h>
#include <assert.h>


/*--- Local defines -----------------------------------------------------*/
#ifndef GRID_UNDEFINED_VALUE
// This will define a value used for undefined values if not provided
// externally.
#  ifdef NAN
#    define GRID_UNDEFINED_VALUE NAN
#  else
#    define GRID_UNDEFINED_VALUE (0.0 / 0.0)
#  endif
#endif

/*--- Implementation of the ADT structure -------------------------------*/
struct grid_struct {
	uint32_t grid1Dim;
	uint64_t numCellsTotal;
	double   boxsize;
	double   timeIndex;
	uint32_t numVariables;
	char     **variableNames;
	fpv_t    **variableData;
	uint32_t sizeSPHKernel;
	double   *kernelSPH;
	uint32_t sizeSPHKernelMedium;
	double   *kernelSPHMedium;
	uint32_t sizeSPHKernelBig;
	double   *kernelSPHBig;
};


/*--- Prototypes of local functions -------------------------------------*/
static void
local_enlargeVariableStorageByN(grid_t grid, int increment);

static char *
local_constructDataFileName(const char *outPrefix, const char *name);

static char *
local_constructBovName(const char *outPrefix, const char *name);

static void
local_writeBov(grid_t grid, const char *dataFname, int varIndex, FILE *f);

static uint32_t
local_calcWeightBaseSizeSPH(fpv_t hsml, uint32_t grid1Dim);

static void
local_assignKernelToAllQuadrants(grid_t   grid,
                                 double   *kernel,
                                 uint32_t weightBaseSize,
                                 double   *x,
                                 uint32_t kernelCell,
                                 double   *weight);

static double *
local_calcKernelSPH(uint32_t kernel1Dim);

static double
local_calcKernelSPHSubSample(const uint32_t *k,
                             double         kernelMin,
                             double         subCellWidth,
                             double         cellWidth);

static double
local_kernelSPH(double r);


/*--- Implementations of exported functions -----------------------------*/
extern grid_t
grid_new(int gridSize)
{
	grid_t grid;

	assert(gridSize > 0 && gridSize < 1025);

	grid                      = xmalloc(sizeof(struct grid_struct));
	grid->grid1Dim            = (uint32_t)gridSize;
	grid->numCellsTotal       = (uint64_t)(gridSize * gridSize * gridSize);
	grid->boxsize             = 0.0;
	grid->timeIndex           = 0.0;
	grid->numVariables        = 0;
	grid->variableNames       = NULL;
	grid->variableData        = NULL;
	grid->sizeSPHKernelBig    = SPHKERNELSIZEBIG;
	grid->kernelSPHBig        = local_calcKernelSPH(SPHKERNELSIZEBIG);
	grid->sizeSPHKernelMedium = SPHKERNELSIZEMEDIUM;
	grid->kernelSPHMedium     = local_calcKernelSPH(SPHKERNELSIZEMEDIUM);
	grid->sizeSPHKernel       = SPHKERNELSIZESMALL;
	grid->kernelSPH           = local_calcKernelSPH(SPHKERNELSIZESMALL);
	return grid;
}

extern void
grid_del(grid_t *grid)
{
	assert(grid != NULL);
	assert(*grid != NULL);

	if ((*grid)->numVariables > 0) {
		for (int i = 0; i < (*grid)->numVariables; i++) {
			xfree((*grid)->variableNames[i]);
			xfree((*grid)->variableData[i]);
		}
		xfree((*grid)->variableNames);
		xfree((*grid)->variableData);
	}
	if ((*grid)->kernelSPH != NULL)
		xfree((*grid)->kernelSPH);
	if ((*grid)->kernelSPHBig != NULL)
		xfree((*grid)->kernelSPHBig);
	if ((*grid)->kernelSPHMedium != NULL)
		xfree((*grid)->kernelSPHMedium);
	xfree(*grid);
	*grid = NULL;
}

extern uint64_t
grid_getNumCellsTotal(grid_t grid)
{
	assert(grid != NULL);
	return grid->numCellsTotal;
}

extern void
grid_setBoxsize(grid_t grid, double boxsize)
{
	assert(grid != NULL);
	assert(boxsize > 0.0);

	grid->boxsize = boxsize;
}

extern void
grid_setTimeIndex(grid_t grid, double timeIndex)
{
	assert(grid != NULL);

	grid->timeIndex = timeIndex;
}

extern int
grid_addVariable(grid_t grid, const char *varName)
{
	int newVarIndex = grid->numVariables;

	assert(grid != NULL);
	assert(varName != NULL);

	local_enlargeVariableStorageByN(grid, 1);
	grid->variableNames[newVarIndex] = xstrdup(varName);
	grid->variableData[newVarIndex]  = xmalloc(sizeof(fpv_t)
	                                           * grid->numCellsTotal);
	grid_assignValueToVarByIndex(grid, newVarIndex, FPV_C(0.0));
	return newVarIndex;
}

extern int
grid_getNumVariables(grid_t grid)
{
	assert(grid != NULL);

	return (int)(grid->numVariables);
}

extern void
grid_assignValueToVarByIndex(grid_t grid, int varIndex, fpv_t value)
{
	assert(grid != NULL);
	assert(varIndex >= 0 && varIndex < grid->numVariables);

#ifdef WITH_OPENMP
#  pragma omp parallel for
#endif
	for (uint64_t i = 0; i < grid->numCellsTotal; i++) {
		grid->variableData[varIndex][i] = value;
	}
}

extern void
grid_getAffectedCells(grid_t         grid,
                      const uint32_t *gridPos,
                      uint32_t       weightBaseSize,
                      uint32_t       *affectedCells)
{
	uint32_t k[NDIM];
	uint32_t i, j;

	for (i = 0; i < POW_NDIM(weightBaseSize); i++) {
		ndim_array_access_lin2n(NDIM, i, weightBaseSize, 0, k);
		for (j = 0; j < NDIM; j++) {
			k[j] += grid->grid1Dim;
			k[j] += gridPos[j] - weightBaseSize / 2;
			k[j] %= grid->grid1Dim;
		}
		affectedCells[i] = ndim_array_access_n2lin(NDIM, grid->grid1Dim,
		                                           0, k);
	}
}

extern void
grid_mapValueToVarByIndex(grid_t         grid,
                          int            varIndex,
                          fpv_t          value,
                          const double   *weights,
                          uint32_t       weightBaseSize,
                          const uint32_t *affectedCells)
{
	for (uint32_t i = 0; i < POW_NDIM(weightBaseSize); i++) {
		fpv_t tmp;
		tmp = (fpv_t)(weights[i] * value);
#ifdef WITH_OPENMP
#  pragma omp atomic
#endif
		grid->variableData[varIndex][affectedCells[i]] += tmp;
	}
}

extern void
grid_writeVarDataByIndex(grid_t grid, const char *outPrefix, int varIndex)
{
	FILE *f;
	char *fname;
#ifdef ENABLE_FORTRAN_RECORDS
	int  blocksize;
#endif

	assert(grid != NULL);
	assert(varIndex >= 0 && varIndex < grid->numVariables);

	fname     = local_constructDataFileName(outPrefix,
	                                        grid->variableNames[varIndex]);
	f         = xfopen(fname, "wb");
#ifdef ENABLE_FORTRAN_RECORDS
	blocksize = grid->numCellsTotal * sizeof(fpv_t);
	fwrite(&blocksize, sizeof(int), 1, f);
#endif
	fwrite(grid->variableData[varIndex], sizeof(fpv_t),
	       grid->numCellsTotal, f);
#ifdef ENABLE_FORTRAN_RECORDS
	fwrite(&blocksize, sizeof(int), 1, f);
#endif
	xfclose(&f);
	xfree(fname);
}

extern void
grid_writeBovForVarDataByIndex(grid_t     grid,
                               const char *outPrefix,
                               int        varIndex)
{
	FILE *f;
	char *fname;
	char *dataFname;

	assert(grid != NULL);
	assert(varIndex >= 0 && varIndex < grid->numVariables);

	fname     = local_constructBovName(outPrefix,
	                                   grid->variableNames[varIndex]);
	dataFname = local_constructDataFileName(outPrefix,
	                                        grid->variableNames[varIndex]);
	f         = xfopen(fname, "w");
	local_writeBov(grid, dataFname, varIndex, f);
	xfclose(&f);
	xfree(dataFname);
	xfree(fname);
}

extern void
grid_convertRealPosToRealGridPos(grid_t      grid,
                                 const fpv_t *realPos,
                                 double      *realGridPos)
{
	assert(grid != NULL);
	assert(realPos != NULL);
	assert(realGridPos != NULL);

	for (int i = 0; i < NDIM; i++)
		realGridPos[i] = realPos[i] * grid->grid1Dim;
}

extern void
grid_convertRealGridPosToGridPos(const double *realGridPos,
                                 uint32_t     *gridPos)
{
	assert(realGridPos != NULL);
	assert(gridPos != NULL);

	for (int i = 0; i < NDIM; i++)
		gridPos[i] = (uint32_t)floor(realGridPos[i]);
}

extern void
grid_calcDistToCellCenter(double *realGridPos, double *dist)
{
	assert(realGridPos != NULL);
	assert(dist != NULL);

	for (int i = 0; i < NDIM; i++)
		dist[i] = realGridPos[i] - (floor(realGridPos[i]) + 0.5);
}

extern uint32_t
grid_getWeightsSPH(grid_t       grid,
                   fpv_t        hsml,
                   const double *dist,
                   double       *weight)
{
	uint32_t weightBaseSize;
	uint32_t i, j;
	uint32_t k[NDIM];
	double   x[NDIM];
	double   scaleKernelToGridCells;
	uint32_t currKernelSize;
	double   *currKernel;
	assert(grid != NULL);
	assert(weight != NULL);
	assert(dist != NULL);
	assert(isgreater(hsml, 0.0));

	if (isless(hsml * grid->grid1Dim, 0.5)) {
		weight[0] = 1.0;
		return 1;
	}
	weightBaseSize = local_calcWeightBaseSizeSPH(hsml, grid->grid1Dim);
	for (i = 0; i < POW_NDIM(weightBaseSize); i++)
		weight[i] = 0.0;

	if (weightBaseSize / 2 < grid->sizeSPHKernel) {
		currKernelSize = grid->sizeSPHKernel;
		currKernel     = grid->kernelSPH;
	} else if (weightBaseSize / 2 < grid->sizeSPHKernelMedium) {
		currKernelSize = grid->sizeSPHKernelMedium;
		currKernel     = grid->kernelSPHMedium;
	} else {
		currKernelSize = grid->sizeSPHKernelBig;
		currKernel     = grid->kernelSPHBig;
	}

	scaleKernelToGridCells = (double)grid->grid1Dim
	                         / (double)currKernelSize * hsml;
	for (i = 0; i < POW_NDIM(currKernelSize); i++) {
		ndim_array_access_lin2n(NDIM, i, currKernelSize, 0, k);
		for (j = 0; j < NDIM; j++)
			x[j] = ((k[j] + 0.5) * scaleKernelToGridCells + dist[j]);
		local_assignKernelToAllQuadrants(grid, currKernel,
		                                 weightBaseSize, x, i,
		                                 weight);
	}

	return weightBaseSize;
} /* grid_getWeightsSPH */

extern uint32_t
grid_getWeightsTSC(const double *dist, double *weight)
{
	double   w[NDIM][3];
	uint32_t k[NDIM];
	uint32_t i, j;
	assert(dist != NULL);
	assert(weight != NULL);

	// Stimmt eigentlich.
	// Wenn Du es mir nicht glaubts, dann mal' es auf.
	// Danke.
	for (i = 0; i < NDIM; i++) {
		w[i][0] = 0.5 * POW2(0.5 - dist[i]);
		w[i][1] = 0.75 - POW2(dist[i]);
		w[i][2] = 0.5 * POW2(0.5 + dist[i]);
	}
	for (i = 0; i < POW_NDIM(3); i++) {
		weight[i] = 1.0;
		ndim_array_access_lin2n(NDIM, i, 3, 0, k);
		for (j = 0; j < NDIM; j++)
			weight[i] *= w[j][k[j]];
	}
	return 3;
}

extern uint32_t
grid_getWeightsCIC(const double *dist, double *weight)
{
	double   w[NDIM][3];
	uint32_t k[NDIM];
	uint32_t i, j;
	assert(dist != NULL);
	assert(weight != NULL);

	for (i = 0; i < NDIM; i++) {
		w[i][0] = (dist[i] < 0.0) ? -1.0 * dist[i] : 0.0;
		w[i][1] = 1.0 - fabs(dist[i]);
		w[i][2] = (dist[i] > 0.0) ? dist[i] : 0.0;
	}
	for (i = 0; i < POW_NDIM(3); i++) {
		weight[i] = 1.0;
		ndim_array_access_lin2n(NDIM, i, 3, 0, k);
		for (j = 0; j < NDIM; j++)
			weight[i] *= w[j][k[j]];
	}
	return 3;
}

extern long double
grid_sumupAllValuesOnVariableByNum(grid_t grid, int varIndex)
{
	long double sum = 0.0;
	assert(grid != NULL);
	assert(varIndex >= 0 && varIndex < grid->numVariables);
#ifdef WITH_OPENMP
#  pragma omp parallel for reduction(+:sum)
#endif
	for (uint64_t i = UINT64_C(0); i < grid->numCellsTotal; i++) {
		sum += grid->variableData[varIndex][i];
	}

	return sum;
}

extern void
grid_divideVariablesByNum(grid_t grid, int varIndex1, int varIndex2)
{
	assert(grid != NULL);
	assert(varIndex1 >= 0 && varIndex1 < grid->numVariables);
	assert(varIndex2 >= 0 && varIndex2 < grid->numVariables);
#ifdef WITH_OPENMP
#  pragma omp parallel for
#endif
	for (uint64_t i = UINT64_C(0); i < grid->numCellsTotal; i++) {
		if (isfinite(grid->variableData[varIndex2][i])
		    && islessgreater(grid->variableData[varIndex2][i], 0.0))
			grid->variableData[varIndex1][i]
			    /= grid->variableData[varIndex2][i];
		else
			grid->variableData[varIndex1][i] = GRID_UNDEFINED_VALUE;
	}
}

extern void
grid_scaleVariablesByNum(grid_t grid, int varIndex, long double scale)
{
	assert(grid != NULL);
	assert(varIndex >= 0 && varIndex < grid->numVariables);
#ifdef WITH_OPENMP
#  pragma omp parallel for
#endif
	for (uint64_t i = UINT64_C(0); i < grid->numCellsTotal; i++) {
		grid->variableData[varIndex][i] *= scale;
	}
}

/*--- Implementations of local functions --------------------------------*/
static void
local_enlargeVariableStorageByN(grid_t grid, int increment)
{
	grid->numVariables += increment;
	grid->variableNames = xrealloc(grid->variableNames,
	                               sizeof(char *) * grid->numVariables);
	grid->variableData  = xrealloc(grid->variableData,
	                               sizeof(fpv_t *) * grid->numVariables);
}

static char *
local_constructDataFileName(const char *outPrefix, const char *name)
{
	char *fname = xmalloc(strlen(outPrefix) + strlen(name) + 6);
	sprintf(fname, "%s.%s.dat", outPrefix, name);
	return fname;
}

static char *
local_constructBovName(const char *outPrefix, const char *name)
{
	char *fname = xmalloc(strlen(outPrefix) + strlen(name) + 6);
	sprintf(fname, "%s.%s.bov", outPrefix, name);
	return fname;
}

static void
local_writeBov(grid_t grid, const char *dataFname, int varIndex, FILE *f)
{
	fprintf(f, "TIME: %f\n", grid->timeIndex);
	fprintf(f, "DATA_FILE: %s\n", dataFname);
	fprintf(f, "DATA_SIZE: %" PRIu32 " %" PRIu32 " %" PRIu32 "\n",
	        grid->grid1Dim, grid->grid1Dim, grid->grid1Dim);
#ifdef ENABLE_DOUBLE
	fprintf(f, "DATA_FORMAT: DOUBLE\n");
#else
	fprintf(f, "DATA_FORMAT: FLOAT\n");
#endif
	fprintf(f, "VARIABLE: %s\n", grid->variableNames[varIndex]);
	if (test_endian() == 0)
		fprintf(f, "DATA_ENDIAN: LITTLE\n");
	else
		fprintf(f, "DATA_ENDIAN: BIG\n");
	fprintf(f, "CENTERING: zonal\n");
	fprintf(f, "BRICK_ORIGIN: 0. 0. 0.\n");
	fprintf(f, "BRICK_SIZE: %f %f %f\n",
	        grid->boxsize, grid->boxsize, grid->boxsize);
#ifdef ENABLE_FORTRAN_RECORDS
	fprintf(f, "BYTE_OFFSET: 4\n");
#endif
}

static uint32_t
local_calcWeightBaseSizeSPH(fpv_t hsml, uint32_t grid1Dim)
{
	uint32_t weightBaseSize;
	weightBaseSize = ((uint32_t)ceil(2.0 * hsml * grid1Dim)) + 1;
	if (weightBaseSize % 2 == 0)
		weightBaseSize++;
	if (weightBaseSize > MAXBASESIZE) {
		fprintf(stderr,
		        "SPH smoothing exceeds %" PRIu32
		        " grid cells, increase MAXBASESIZE\n",
		        weightBaseSize);
		exit(EXIT_FAILURE);
	}
	return weightBaseSize;
}

static void
local_assignKernelToAllQuadrants(grid_t   grid,
                                 double   *kernel,
                                 uint32_t weightBaseSize,
                                 double   *x,
                                 uint32_t kernelCell,
                                 double   *weight)
{
	uint32_t perm = 1;
	uint32_t mask;
	uint32_t gridPos[NDIM];
	uint32_t idx;
	double   center = (double)weightBaseSize / 2.0;
	int      flip;
	int      i, j;

	// This loops over all quadrants, the nasty masking and shifting and
	// fliping is a fast way to address the different quadrants:  you
	// will need to draw that on a map to understand what it does...
	for (i = 0; i < POW_NDIM(2); i++) {
		mask = 1;
		for (j = 0; j < NDIM; j++) {
			flip = ((perm & mask) == mask) ? 1 : -1;
			// Technically it should be floor(), but that is slow. A
			// cast to uint32_t should be correct for the case at hand.
			gridPos[j] = (uint32_t)(center + flip * x[j]);
			mask     <<= 1;
		}
		idx          = ndim_array_access_n2lin(NDIM, weightBaseSize,
		                                       0, gridPos);
		weight[idx] += kernel[kernelCell];
		perm++;
	}
}

static double *
local_calcKernelSPH(uint32_t kernel1Dim)
{
	double   kernelMin      = 0.0;
	double   kernelMax      = 1.0;
	double   norm           = 0.0;
	double   cellWidth      = (kernelMax - kernelMin) / kernel1Dim;
	uint32_t numCells       = POW_NDIM(kernel1Dim);
	double   subCellWidth   = 1. / SPHKERNEL_SUBSAMPLING;
	double   *kernelWeights = xmalloc(sizeof(double) * numCells);

#ifdef WITH_OPENMP
#  pragma omp parallel for reduction(+:norm)
#endif
	for (uint32_t i = 0; i < POW_NDIM(kernel1Dim); i++) {
		uint32_t k[NDIM];
		ndim_array_access_lin2n(NDIM, i, kernel1Dim, 0, k);
		kernelWeights[i] = local_calcKernelSPHSubSample(k, kernelMin,
		                                                subCellWidth,
		                                                cellWidth);
		norm += kernelWeights[i];
	}
	printf("norm = %g\n", norm);
	norm = 1. / (POW_NDIM(2) * norm);
	printf("norm = %g\n", norm);
#ifdef WITH_OPENMP
#  pragma omp parallel for
#endif
	for (uint32_t i = 0; i < POW_NDIM(kernel1Dim); i++) {
		kernelWeights[i] *= norm;
	}

	{
		FILE *f;
		f = fopen("kernel.dat", "wb");
		fwrite(kernelWeights, sizeof(double), POW_NDIM(kernel1Dim), f);
		fclose(f);
	}

	return kernelWeights;
} /* local_calcKernelSPH */

static double
local_calcKernelSPHSubSample(const uint32_t *k,
                             double         kernelMin,
                             double         subCellWidth,
                             double         cellWidth)
{
	uint32_t kSub[NDIM];
	double   r, pos;
	double   subSample = 0.0;

	for (uint32_t j = 0; j < POW_NDIM(SPHKERNEL_SUBSAMPLING); j++) {
		ndim_array_access_lin2n(NDIM, j, SPHKERNEL_SUBSAMPLING, 0, kSub);
		r = 0.0;
		for (uint32_t n = 0; n < NDIM; n++) {
			pos = kernelMin
			      + (k[n] + (kSub[n] + 0.5) * subCellWidth) * cellWidth;
			r  += pos * pos;
		}
		subSample += local_kernelSPH(sqrt(r));
	}
	return subSample;
}

static double
local_kernelSPH(double r)
{
	if (r <= 0.5) {
		return 1. - 6. * POW2(r) + 6. * POW3(r);
	} else if (r <= 1.0) {
		return 2. * POW3(1. - r);
	}
	return 0.0;
}
