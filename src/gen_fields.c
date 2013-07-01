// Copyright (C) 2010, Steffen Knollmann, Adrian M. Partl
// Released under the terms of the GNU General Public License version 3.


/*--- Includes ----------------------------------------------------------*/
#include "../version.h"
#include "../config.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#ifdef WITH_OPENMP
#  include <omp.h>
#endif
#include "libutil/xmem.h"
#include "libutil/xstring.h"
#include "libadts/grid.h"
#include "libadts/partBuffer.h"
#include "libadts/part.h"
#include "writeGrid.h"
#include "mapParticlesToGrid.h"
#include "normalizeGrids.h"


/*--- Local defines -----------------------------------------------------*/
#define PRINT_USAGE(f, name)                                          \
    fprintf((f), "Usage: %s <grid size> <snapshot name> "             \
                 "<snapshot type> <buffer size> <output prefix>\n\n", \
            name);


/*--- Local variables ---------------------------------------------------*/
int            gridSize;
char           *finName;
io_file_type_t finType;
char           *foutPrefix;
uint64_t       bufferSize;


/*--- Prototypes of local functions -------------------------------------*/
static void
local_parse_cmdline(int argc, char **argv);

static void
local_startup(io_logging_t *log, grid_t *grid, partBuffer_t *pbuf);

static void
local_shutdown(io_logging_t *log, grid_t *grid, partBuffer_t *pbuf);

static void
local_describeCode(void);

static io_logging_t
local_startLogging(void);

static grid_t
local_getGrid(void);

static partBuffer_t
local_getPartBuffer(io_logging_t log);


/*--- M A I N -----------------------------------------------------------*/
int
main(int argc, char **argv)
{
	io_logging_t log;
	grid_t       grid;
	partBuffer_t pbuf;

	local_parse_cmdline(argc, argv);
	local_startup(&log, &grid, &pbuf);

	mapParticlesToGrid(pbuf, grid);
	normalizeGrids(grid);
	writeGrid(grid, foutPrefix);

	local_shutdown(&log, &grid, &pbuf);

	return EXIT_SUCCESS;
}

/*--- Implementations of local functions --------------------------------*/
static void
local_parse_cmdline(int argc, char **argv)
{
	if (argc != 6) {
		if (argc == 2 && argv[1][0] == '-' && argv[1][1] == 'h') {
			bufferSize = UINT64_MAX;
			local_describeCode();
			PRINT_USAGE(stderr, argv[0]);
			exit(EXIT_SUCCESS);
		}
		PRINT_USAGE(stderr, argv[0]);
		exit(EXIT_FAILURE);
	}
	gridSize = atoi(argv[1]);
	if ((gridSize < 1) || (gridSize > 1024)) {
		fprintf(stderr, "FATAL:  Grid size must be between 1 and 1024.\n\n");
		exit(EXIT_FAILURE);
	}
	finName    = xstrdup(argv[2]);
	finType    = (io_file_type_t)atoi(argv[3]);
	bufferSize = (uint64_t)atol(argv[4]);
	foutPrefix = xstrdup(argv[5]);
}

static void
local_startup(io_logging_t *log, grid_t *grid, partBuffer_t *pbuf)
{
	local_describeCode();
	*log  = local_startLogging();
	*grid = local_getGrid();
	*pbuf = local_getPartBuffer(*log);
}

static void
local_shutdown(io_logging_t *log, grid_t *grid, partBuffer_t *pbuf)
{
	partBuffer_del(pbuf);
	grid_del(grid);
	io_logging_stop(log);
	xfree(foutPrefix);
	xfree(finName);
#ifdef XMEM_TRACK_MEM
	xmem_info(stdout);
#endif
}

static void
local_describeCode(void)
{
	PRINT_VERSION_INFO(stdout);
	printf("\nThese are the characteristics of the code:\n");
#ifdef ENABLE_DOUBLE
	printf("\to Using double precision\n");
#else
	printf("\to Using single precision\n");
#endif
#ifdef WITH_MAPPING_CIC
	printf("\to Using CIC mapping for particles\n");
#else
	printf("\to Using TSC mapping for particles\n");
#endif
#ifdef WITH_MAPPING_SPH
	printf("\to Using SPH mapping for gas particles\n");
#endif
	if (bufferSize != UINT64_MAX)
		printf("\to Using a buffer for %" PRIu64 " particles (%fMB)\n",
		       bufferSize, bufferSize * part_getSizeOf1Part()
		       / (1024. * 1024.));
#ifdef WITH_OPENMP
	printf("\to Using OpenMP with %i threads\n",
	       omp_get_max_threads());
#endif
#ifdef ENABLE_FORTRAN_RECORDS
	printf("\to Output files will have Fortran block delimiters\n");
#endif
	printf("\n\n");
}

static io_logging_t
local_startLogging(void)
{
	return io_logging_start("-", 0,
	                        IO_LOGGING_FLAGS_DUPLICATE_CRITICAL
	                        | IO_LOGGING_FLAGS_USE_STDOUT_FOR_CRITICAL);
}

static grid_t
local_getGrid(void)
{
	grid_t grid = grid_new(gridSize);
	(void)grid_addVariable(grid, "dens");
	(void)grid_addVariable(grid, "vx");
	(void)grid_addVariable(grid, "vy");
	(void)grid_addVariable(grid, "vz");
	(void)grid_addVariable(grid, "gasdens");
	(void)grid_addVariable(grid, "temperature");
	return grid;
}

static partBuffer_t
local_getPartBuffer(io_logging_t log)
{
	partBuffer_t pbuf;
#ifdef USE_FAKE_PARTICLES
	pbuf = partBuffer_new(NUM_FAKE_PARTICLES);
	partBuffer_setFakeParticles(pbuf, NUM_FAKE_PARTICLES);
#else
	pbuf = partBuffer_new(bufferSize);
	partBuffer_readyFile(pbuf, finName, finType, log);
#endif
	return pbuf;
}
