// Copyright (C) 2010, Steffen Knollmann
// Released under the terms of the GNU General Public License version 3.
// This file is part of `densfield'.


/*--- Includes ----------------------------------------------------------*/
#include "../../config.h"
#include "partBuffer.h"
#include "../libutil/xmem.h"
#include <inttypes.h>
#include <assert.h>


/*--- Implementation of the ADT structure -------------------------------*/
struct partBuffer_struct {
	uint64_t              numPartsBuffer;
	uint64_t              partsInBuffer;
	part_t                parts;
	io_logging_t          log;
	io_file_t             f;
	uint64_t              ptotal;
	uint64_t              pskip;
	uint64_t              pread;
	double                boxsize;
	double                expansion;
	io_file_strg_struct_t strg;
};


/*--- Prototypes of local functions -------------------------------------*/


/*--- Implementations of exported functions -----------------------------*/
extern partBuffer_t
partBuffer_new(uint64_t numPartsBuffer)
{
	partBuffer_t pbuf;

	assert(numPartsBuffer > 0);

	pbuf                 = xmalloc(sizeof(struct partBuffer_struct));
	pbuf->numPartsBuffer = numPartsBuffer;
	pbuf->partsInBuffer  = UINT64_C(0);
	pbuf->parts          = part_newBunch(numPartsBuffer);
	pbuf->log            = NULL;
	pbuf->f              = NULL;
	pbuf->ptotal         = UINT64_C(0);
	pbuf->pskip          = UINT64_C(0);
	pbuf->pread          = UINT64_MAX;
	pbuf->boxsize        = FPV_C(1.0);
	pbuf->expansion      = FPV_C(0.5);
	part_fillOffsetInformation(pbuf->parts, &(pbuf->strg));
	return pbuf;
}

extern void
partBuffer_del(partBuffer_t *pbuf)
{
	assert(pbuf != NULL);
	assert(*pbuf != NULL);

	if ((*pbuf)->parts != NULL)
		part_del(&((*pbuf)->parts));
	if ((*pbuf)->f != NULL)
		io_file_close((*pbuf)->log, &((*pbuf)->f));
	xfree(*pbuf);
	*pbuf = NULL;
}

extern double
partBuffer_getBoxsize(partBuffer_t pbuf)
{
	assert(pbuf != NULL);
	return pbuf->boxsize;
}

extern double
partBuffer_getExpansion(partBuffer_t pbuf)
{
	assert(pbuf != NULL);
	return pbuf->expansion;
}

extern void
partBuffer_readyFile(partBuffer_t   pbuf,
                     const char     *fname,
                     io_file_type_t ftype,
                     io_logging_t   log)
{
	assert(pbuf != NULL);

	pbuf->log = log;
	pbuf->f   = io_file_open(log, (char *)fname, ftype,
	                         IO_FILE_UNKOWN_SWAPPING,
	                         IO_FILE_READ, 1);
	if (pbuf->f == NULL)
		exit(EXIT_FAILURE);
	io_file_init(log, pbuf->f);
	pbuf->ptotal = io_file_get_numpart(log, pbuf->f, &(pbuf->pskip),
	                                   &(pbuf->pread));
	io_file_get(pbuf->log, pbuf->f, IO_FILE_GET_BOXSIZE, &(pbuf->boxsize));
	io_file_get(pbuf->log, pbuf->f, IO_FILE_GET_A, &(pbuf->expansion));
}

extern void
partBuffer_setFakeParticles(partBuffer_t pbuf, int numFakeParts)
{
	assert(pbuf != NULL);
	assert(numFakeParts <= pbuf->numPartsBuffer);

	pbuf->partsInBuffer = numFakeParts;
	part_setFakeParticles(pbuf->parts, numFakeParts);
}

extern uint64_t
partBuffer_numPartsAvailable(partBuffer_t pbuf)
{
	assert(pbuf != NULL);
	return pbuf->partsInBuffer;
}

extern part_t
partBuffer_getPartByIndex(partBuffer_t pbuf, uint64_t index)
{
	assert(pbuf != NULL);
	assert(index < UINT64_MAX);
	return part_getPartInBunch(pbuf->parts, index);
}

extern void
partBuffer_refillBuffer(partBuffer_t pbuf)
{
	part_t part;
	double velFac;
	assert(pbuf != NULL);

	if (pbuf->f == NULL) {
		pbuf->partsInBuffer = UINT64_C(0);
		return;
	}
	pbuf->pread = pbuf->numPartsBuffer;
	if (pbuf->pread+pbuf->pskip > pbuf->ptotal)
		pbuf->pread = pbuf->ptotal - pbuf->pskip;
	if (pbuf->pread == 0) {
		pbuf->partsInBuffer = UINT64_C(0);
		return;
	}
	pbuf->partsInBuffer = io_file_readpart(pbuf->log, pbuf->f,
	                                       pbuf->pskip, pbuf->pread,
	                                       pbuf->strg);
	pbuf->pskip += pbuf->partsInBuffer;
	velFac = pbuf->boxsize * 100. / pbuf->expansion;
#ifdef WITH_OPENMP
#  pragma omp parallel for private(part)
#endif
	for (uint64_t i = UINT64_C(0); i < pbuf->partsInBuffer; i++) {
		part = part_getPartInBunch(pbuf->parts, i);
		part_scaleVelocity(part, velFac);
	}
}

/*--- Implementations of local functions --------------------------------*/
