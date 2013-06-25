// Copyright (C) 2010, Steffen Knollmann
// Released under the terms of the GNU General Public License version 3.
// This file is part of `densfield'.


#ifndef GRID_H
#define GRID_H


/*--- Includes ----------------------------------------------------------*/
#include "../../config.h"
#include <stdint.h>


/*--- ADT handle --------------------------------------------------------*/
typedef struct grid_struct *grid_t;


/*--- Prototypes of exported functions ----------------------------------*/
extern grid_t
grid_new(int gridSize);

extern void
grid_del(grid_t *grid);

extern uint64_t
grid_getNumCellsTotal(grid_t grid);

extern void
grid_setBoxsize(grid_t grid, double boxsize);

extern void
grid_setTimeIndex(grid_t grid, double timeIndex);

extern int
grid_addVariable(grid_t grid, const char *varName);

extern int
grid_getNumVariables(grid_t grid);

extern void
grid_assignValueToVarByIndex(grid_t grid, int varIndex, fpv_t value);

extern void
grid_getAffectedCells(grid_t         grid,
                      const uint32_t *gridPos,
                      uint32_t       weightBaseSize,
                      uint32_t       *affectedCells);

extern void
grid_mapValueToVarByIndex(grid_t         grid,
                          int            varIndex,
                          fpv_t          value,
                          const double   *weights,
                          uint32_t       weightBaseSize,
                          const uint32_t *affectedCells);

extern void
grid_writeVarDataByIndex(grid_t grid, const char *outPrefix, int varIndex);

extern void
grid_writeBovForVarDataByIndex(grid_t     grid,
                               const char *outPrefix,
                               int        varIndex);

extern void
grid_convertRealPosToRealGridPos(grid_t      grid,
                                 const fpv_t *realPos,
                                 double      *realGridPos);

extern void
grid_convertRealGridPosToGridPos(const double *realGridPos,
                                 uint32_t     *gridPos);

extern void
grid_calcDistToCellCenter(double *realGridPos, double *dist);

extern uint32_t
grid_getWeightsSPH(grid_t       grid,
                   fpv_t        hsml,
                   const double *dist,
                   double       *weight);

extern uint32_t
grid_getWeightsTSC(const double *dist, double *weight);

extern uint32_t
grid_getWeightsCIC(const double *dist, double *weight);

extern long double
grid_sumupAllValuesOnVariableByNum(grid_t grid, int varIndex);

extern void
grid_divideVariablesByNum(grid_t grid, int varIndex1, int varIndex2);

extern void
grid_scaleVariablesByNum(grid_t grid, int varIndex, long double scale);


#endif
