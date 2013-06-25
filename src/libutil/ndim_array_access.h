#ifndef NDIM_ARRAY_ACCESS_H
#define NDIM_ARRAY_ACCESS_H

/**
 * \file  ndim_array_index.h
 *
 *  Provides functions to convert a linear array index into a
 *  n-dimensional position in an base^n sized n-cube and vice versa.
 */


/***********************************************************************\
 *    Includes                                                         *
\***********************************************************************/
#include <stdint.h>


/***********************************************************************\
 *    Implementation of exported functions                             * 
\***********************************************************************/
inline extern uint32_t
ndim_array_access_n2lin(uint32_t n,
                        uint32_t base,
                        uint32_t offset,
                        const uint32_t *ndim_index)
{
	uint32_t i;
	uint32_t index;
	uint32_t tmp;

	tmp = 1;
	index = 0;
	for (i=0; i<n; i++) {
		index += (ndim_index[i]-offset)*tmp;
		tmp*=base;
	}

	return index;
}

inline extern void
ndim_array_access_lin2n(uint32_t n,
                        uint32_t linear_index,
                        uint32_t base,
                        uint32_t offset,
                        uint32_t *ndim_index)
{
	uint32_t j;

	for (j=0; j<n; j++) {
		ndim_index[j] = linear_index%base + offset;
		linear_index /= base;
	}

	return;
}


#endif /* NDIM_ARRAY_ACCESS_H */
