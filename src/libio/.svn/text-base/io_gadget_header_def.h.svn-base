// Copyright (C) 2010, Steffen Knollmann
// Released under the terms of the GNU General Public License version 3.


#ifndef IO_GADGET_HEADER_DEF_H
#define IO_GADGET_HEADER_DEF_H


/*--- Includes ----------------------------------------------------------*/
#include <inttypes.h>


/*--- Exported defines --------------------------------------------------*/
// The size (in bytes) reserved at the beginning of a file for the header
#define GADGET_HEADER_SIZE 256

// Defines the total used size (in bytes) of the header
#define GADGET_HEADER_HEADERSIZE (13 * sizeof(int32_t)    \
                                  + 12 * sizeof(uint32_t) \
                                  + 12 * sizeof(double))

// Defines the number of unused bytes in the header
#define GADGET_HEADER_FILLHEADER (GADGET_HEADER_SIZE \
                                  - GADGET_HEADER_HEADERSIZE)


/*--- ADT handle --------------------------------------------------------*/
typedef struct io_gadget_header_struct io_gadget_header_struct_t;
typedef io_gadget_header_struct_t      *io_gadget_header_t;


/*--- Implementation of the ADT structure -------------------------------*/
struct io_gadget_header_struct {
	int32_t  np[6];
	double   massarr[6];
	double   expansion;
	double   redshift;
	int32_t  flagsfr;
	int32_t  flagfeedback;
	uint32_t nall[6];
	int32_t  flagcooling;
	int32_t  numfiles;
	double   boxsize;
	double   omega0;
	double   omegalambda;
	double   hubbleparameter;
	int32_t  flagstellarage;
	int32_t  flagmetals;
	uint32_t nallhighw[6];
	int32_t  flagentropyu;
	char     unused[GADGET_HEADER_FILLHEADER];
};


#endif
