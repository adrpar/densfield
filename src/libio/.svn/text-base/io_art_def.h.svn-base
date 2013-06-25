// Copyright (C) 2010, Steffen Knollmann
// Released under the terms of the GNU General Public License version 3.


#ifndef IO_ART_DEF_H
#define IO_ART_DEF_H


/*--- Includes ----------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include "io_art_header_def.h"
#include "io_file.h"


/*--- ADT handle --------------------------------------------------------*/
typedef struct io_art_struct io_art_struct_t;
typedef io_art_struct_t      *io_art_t;


/*--- Implementation of the ADT structure -------------------------------*/
struct io_art_struct {
	io_file_type_t  ftype;
#ifdef WITH_MPI
	int             rank;
	int             size;
	MPI_Comm        mycomm;
	int             size_mycomm;
	int             rank_mycomm;
#endif
	FILE            *file;
	char            *fname;
	io_file_mode_t  mode;
	io_file_swap_t  swapped;
	int8_t          ver;
	int32_t         headsize;
	uint64_t        no_part;
	uint64_t        no_part_with_mass;
	int8_t          multimass;
	double          mmass;
	double          minweight;
	double          maxweight;
	double          sumweight;
	int32_t         no_species;
	double          minpos[3];
	double          maxpos[3];
	double          posscale;
	double          weightscale;
	io_art_header_t header;
};


#endif
