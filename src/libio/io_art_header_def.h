// Copyright (C) 2010, Steffen Knollmann
// Released under the terms of the GNU General Public License version 3.


#ifndef IO_ART_HEADER_DEF_H
#define IO_ART_HEADER_DEF_H


/*--- Includes ----------------------------------------------------------*/
#include <inttypes.h>


/*--- Exported defines --------------------------------------------------*/
// The size (in bytes) reserved at the beginning of a file for the header
#define ART_HEADER_SIZE 529

// We actually store additional information in the header structure
#define ART_HEADER_EXTRA 48


/*--- ADT handle --------------------------------------------------------*/
typedef struct io_art_header_struct io_art_header_struct_t;
typedef io_art_header_struct_t      *io_art_header_t;


/*--- Implementation of the ADT structure -------------------------------*/
struct io_art_header_struct {
	char     header_string[46];
	float    aexpn;
	float    aexp0;
	float    amplt;
	float    astep;
	int      istep;
	float    partw;
	float    tintg;
	float    ekin;
	float    ekin1;
	float    ekin2;
	float    au0;
	float    aeu0;
	int      nrowc;
	int      ngridc;
	int      nspecies;
	int      nseed;
	float    Om0;
	float    Oml0;
	float    hubble;
	float    wp5;
	float    Ocurv;
	float    extras[100];
	/* additional information */
	double   boxsize;
	double   munit;
	double   nvpart;
	uint64_t N_particles;
	uint64_t N_pages;
	uint64_t N_in_last;
};


#endif
