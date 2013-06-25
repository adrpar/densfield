// Copyright (C) 2010, Steffen Knollmann
// Released under the terms of the GNU General Public License version 3.
// This file is part of `densfield'.


#ifndef PARTBUFFER_H
#define PARTBUFFER_H


/*--- Includes ----------------------------------------------------------*/
#include "../../config.h"
#include "part.h"
#include "../libio/io_file.h"
#include <stdint.h>


/*--- ADT handle --------------------------------------------------------*/
typedef struct partBuffer_struct *partBuffer_t;


/*--- Prototypes of exported functions ----------------------------------*/
extern partBuffer_t
partBuffer_new(uint64_t numPartsBuffer);

extern void
partBuffer_readyFile(partBuffer_t   pbuf,
                     const char     *fname,
                     io_file_type_t ftype,
                     io_logging_t   log);

extern void
partBuffer_setFakeParticles(partBuffer_t pbuf, int numFakeParts);

extern void
partBuffer_del(partBuffer_t *pbuf);

extern double
partBuffer_getBoxsize(partBuffer_t pbuf);

extern double
partBuffer_getExpansion(partBuffer_t pbuf);

extern uint64_t
partBuffer_numPartsAvailable(partBuffer_t pbuf);

extern part_t
partBuffer_getPartByIndex(partBuffer_t pbuf, uint64_t index);

extern void
partBuffer_refillBuffer(partBuffer_t pbuf);


#endif
