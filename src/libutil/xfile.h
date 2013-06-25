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


#ifndef XFILE_H
#define XFILE_H

/**
 * \file  xfile.h
 *
 * This will provide wrapper functions for the file routines.
 */


/************************************************************************\
 *    Includes                                                          * 
\************************************************************************/
#include <stdlib.h>
#include <stdio.h>


/************************************************************************\
 *    Defines                                                           * 
\************************************************************************/


/************************************************************************\
 *    Definitions of exported variables                                 * 
\************************************************************************/


/************************************************************************\
 *    Prototypes of exported functions                                  * 
\************************************************************************/

/**
 * \brief  A wrapper function for fopen.
 *
 * This function will abort the program, if the file could not be
 * opened.
 *
 * \param  *path  The name of the file to open.
 * \param  *mode  The mode with which to open, see fopen(3).
 *
 * \return  Returns a file pointer to the opened file.
 */
extern FILE *
xfopen(const char *path, const char *mode);

/**
 * \brief  A wrapper function for fclose.
 *
 * This function will close the given file stream and also set the
 * variable holding the stream to NULL.
 *
 * \param  **fp  Pointer to the variable holding the stream;
 * 
 * \return  This function will always return 0.
 */
extern int
xfclose(FILE **fp);

/**
 * \brief  A wrapper function for fread that will abort the program, if
 *         the read did not succeed.
 *
 * \param  *ptr     A pointer to the external variable that will hold
 *                  the results.  This needs to be large enough.
 * \param  size     The size in bytes of one element.
 * \param  nmemb    The number of elements to read.
 * \param  *stream  The stream to read from.
 *
 * \return  This function always returns nmemb.
 */
extern size_t
xfread(void *ptr, size_t size, size_t nmemb, FILE *stream);

/**
 * \brief  A wrapper function for fwrite that will abort the program if
 *         anything went wrong.
 *
 * \param  *ptr     The pointer to the data which should be printed.
 * \param  size     The size of one element.
 * \param  nmemb    The number of elements to write.
 * \param  *stream  The stream to write to.
 *
 * \return  This function always returns nmemb.
 */
extern size_t
xfwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);

/**
 * \brief  A wrapper function for fseek that will terminate the program
 *         in the occurrence of errors.
 *
 * \param  *stream  The stream to seek in.
 * \param  offset   The offset.
 * \param  whence   The anchor of the offset.
 *
 * \return  This function will always return 0.
 */
extern int
xfseek(FILE *stream, long offset, int whence);


#endif /* XFILE_H */
