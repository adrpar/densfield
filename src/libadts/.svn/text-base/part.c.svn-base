// Copyright (C) 2010, Steffen Knollmann
// Released under the terms of the GNU General Public License version 3.
// This file is part of `densfield'.


/*--- Includes ----------------------------------------------------------*/
#include "../../config.h"
#include "part.h"
#include "../libutil/xmem.h"
#include <inttypes.h>
#include <math.h>
#include <assert.h>


/*--- Implementation of the ADT structure -------------------------------*/
struct part_struct {
	fpv_t    pos[NDIM];
	fpv_t    vel[NDIM];
	fpv_t    mass;
	fpv_t    u;
	fpv_t    hsml;
	uint32_t id;
};


/*--- Prototypes of local functions -------------------------------------*/


/*--- Implementations of exported functions -----------------------------*/
extern part_t
part_newBunch(uint64_t numParts)
{
	part_t part;

	assert(numParts > UINT64_C(0) && numParts < UINT64_MAX);

	part = xmalloc(sizeof(struct part_struct) * numParts);
	for (uint64_t i = 0; i < numParts; i++) {
		for (int j = 0; j < NDIM; j++) {
			part[i].pos[j] = FPV_C(0.0);
			part[i].vel[j] = FPV_C(0.0);
		}
		part[i].mass = FPV_C(0.0);
		part[i].u    = FPV_C(-1.0); // default to no gas
		part[i].hsml = FPV_C(0.0);
		part[i].id   = UINT32_C(0);
	}
	return part;
}

extern void
part_del(part_t *part)
{
	assert(part != NULL);
	assert(*part != NULL);

	xfree(*part);
}

extern fpv_t *
part_getRealPos(part_t part)
{
	assert(part != NULL);
	return part->pos;
}

extern fpv_t
part_getMass(part_t part)
{
	assert(part != NULL);
	return part->mass;
}

extern fpv_t
part_getVel(part_t part, int component)
{
	assert(part != NULL);
	assert(component >= 0 && component < NDIM);
	return part->vel[component];
}

extern fpv_t
part_getU(part_t part)
{
	assert(part != NULL);
	return part->u;
}

extern fpv_t
part_getHsml(part_t part)
{
	assert(part != NULL);
	return part->hsml;
}

extern bool
part_isSPHParticle(part_t part)
{
	assert(part != NULL);

	if (isgreaterequal(part->u, FPV_C(0.0)))
		return true;

	return false;
}

extern void
part_fillOffsetInformation(part_t part, io_file_strg_struct_t *strg)
{
	struct part_struct strideParts[2];
	strg->posx.val    = &(part->pos[0]);
	strg->posx.stride = (char *)&(strideParts[1].pos[0])
	                    - (char *)&(strideParts[0].pos[0]);
	strg->momx.val    = &(part->vel[0]);
	strg->momx.stride = (char *)&(strideParts[1].vel[0])
	                    - (char *)&(strideParts[0].vel[0]);
#if (NDIM >= 2)
	strg->posy.val    = &(part->pos[1]);
	strg->posy.stride = (char *)&(strideParts[1].pos[1])
	                    - (char *)&(strideParts[0].pos[1]);
	strg->momy.val    = &(part->vel[1]);
	strg->momy.stride = (char *)&(strideParts[1].vel[1])
	                    - (char *)&(strideParts[0].vel[1]);
#endif
#if (NDIM >= 3)
	strg->posz.val    = &(part->pos[2]);
	strg->posz.stride = (char *)&(strideParts[1].pos[2])
	                    - (char *)&(strideParts[0].pos[2]);
	strg->momz.val    = &(part->vel[2]);
	strg->momz.stride = (char *)&(strideParts[1].vel[2])
	                    - (char *)&(strideParts[0].vel[2]);
#endif
	strg->weight.val    = &(part->mass);
	strg->weight.stride = (char *)&(strideParts[1].mass)
	                      - (char *)&(strideParts[0].mass);
	strg->u.val         = &(part->u);
	strg->u.stride      = (char *)&(strideParts[1].u)
	                      - (char *)&(strideParts[0].u);
	strg->hsml.val      = &(part->hsml);
	strg->hsml.stride   = (char *)&(strideParts[1].hsml)
	                      - (char *)&(strideParts[0].hsml);
	strg->id.val        = &(part->id);
	strg->id.stride     = (char *)&(strideParts[1].id)
	                      - (char *)&(strideParts[0].id);
	strg->bytes_float   = sizeof(part->pos[0]);
	strg->bytes_int     = sizeof(part->id);
} /* part_fillOffsetInformation */

extern void
part_setFakeParticles(part_t part, int numFakeParts)
{
	double tmp;
	int    i, j;
	assert(part != NULL);

	for (i = 0; i < numFakeParts; i++) {
		for (j = 0; j < NDIM - 1; j++) {
			tmp            = 1. / (2 * 15.) + 2. / 15. * i;
			tmp            = fmod(tmp, 1.0);
			part[i].pos[j] = (fpv_t)tmp;
			part[i].vel[j] = FPV_C(3242.3213);
		}
		part[i].pos[j] = FPV_C(0.5);
		part[i].vel[j] = FPV_C(3242.3213);
		part[i].mass   = FPV_C(50.24);
		part[i].u      = FPV_C(123.123);
		part[i].hsml   = FPV_C(0.2);
		part[i].id     = UINT32_C(2341);
	}
}

extern part_t
part_getPartInBunch(part_t part, uint64_t index)
{
	assert(part != NULL);
	assert(index < UINT64_MAX);
	return part + index;
}

extern void
part_scaleVelocity(part_t part, double velFac)
{
	assert(part != NULL);
	assert(velFac != 0.0);

	for (int i = 0; i < NDIM; i++) {
		part->vel[i] *= (fpv_t)velFac;
	}
}

extern size_t
part_getSizeOf1Part(void)
{
	return sizeof(struct part_struct);
}

/*--- Implementations of local functions --------------------------------*/
