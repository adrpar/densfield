/* 
 * Copyright (C) 2009, Steffen Knollmann
 * 
 * This file is part of `mtree2'.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA. 
 */


/**
 * \file  xfile.c
 *
 * This will provide wrapper functions for file routines.
 */


/************************************************************************\
 *    Includes                                                          * 
\************************************************************************/
#include "xfile.h"
#include <stdlib.h>
#include <stdio.h>


/************************************************************************\
 *    Defines                                                           * 
\************************************************************************/


/************************************************************************\
 *    Implementations of exported variables                             * 
\************************************************************************/


/************************************************************************\
 *    Prototypes of local functions                                     * 
\************************************************************************/


/************************************************************************\
 *    Implementations of exported functions                             * 
\************************************************************************/
extern FILE *
xfopen(const char *path, const char *mode)
{
	FILE *dummy = fopen(path, mode);

	if (dummy == NULL) {
		fprintf(stderr, "Could not open %s with mode %s..\n",
		        path, mode);
		fprintf(stderr, "Exiting... :-(\n");
		exit(EXIT_FAILURE);
	}

	return dummy;
}

extern int
xfclose(FILE **fp)
{
	if ( (fp == NULL) || ((*fp) == NULL) )
		return 0;

	fclose(*fp);
	*fp = NULL;

	return 0;
}

extern size_t
xfread(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
	if (fread(ptr, size, nmemb, stream) != nmemb) {
		fprintf(stderr,
		        "Expected to read %li (%lib each) but got less.\n",
		        (long)nmemb, (long)size);
		fprintf(stderr, "Exiting... :-(\n");
		exit(EXIT_FAILURE);
	}

	return nmemb;
}

extern size_t
xfwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
{
	if (fwrite(ptr, size, nmemb, stream) != nmemb) {
		fprintf(stderr,
		        "Expected to write %li (%lib each) but wrote less.\n",
		        (long)nmemb, (long)size);
		fprintf(stderr, "Exiting... :-(\n");
		exit(EXIT_FAILURE);
	}

	return nmemb;
}

extern int
xfseek(FILE *stream, long offset, int whence)
{
	if (!fseek(stream, offset, whence)) {
		fprintf(stderr,
		        "Seeking did not yield in the anticipated result.\n");
		fprintf(stderr, "Exiting... :-(\n");
		exit(EXIT_FAILURE);
	}

	return 0;
}
