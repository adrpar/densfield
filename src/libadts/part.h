// Copyright (C) 2010, Steffen Knollmann
// Released under the terms of the GNU General Public License version 3.
// This file is part of `densfield'.


#ifndef PART_H
#define PART_H


/*--- Includes ----------------------------------------------------------*/
#include "../../config.h"
#include <stdint.h>
#include <stdbool.h>
#include "../libio/io_file_aux.h"


/*--- ADT handle --------------------------------------------------------*/
typedef struct part_struct *part_t;


/*--- Prototypes of exported functions ----------------------------------*/
extern part_t
part_newBunch(uint64_t numParts);

extern void
part_del(part_t *part);

extern fpv_t *
part_getRealPos(part_t part);

extern fpv_t
part_getMass(part_t part);

extern fpv_t
part_getVel(part_t part, int component);

extern fpv_t
part_getU(part_t part);

extern fpv_t
part_getHsml(part_t part);

extern bool
part_isSPHParticle(part_t part);

extern void
part_fillOffsetInformation(part_t part, io_file_strg_struct_t *strg);

extern void
part_setFakeParticles(part_t part, int numFakeParts);

extern part_t
part_getPartInBunch(part_t part, uint64_t index);

extern void
part_scaleVelocity(part_t part, double velFac);

extern size_t
part_getSizeOf1Part(void);

#endif
