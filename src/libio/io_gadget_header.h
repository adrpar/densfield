// Copyright (C) 2010, Steffen Knollmann
// Released under the terms of the GNU General Public License version 3.


#ifndef IO_GADGET_HEADER_H
#define IO_GADGET_HEADER_H


/*--- Includes ----------------------------------------------------------*/
#include "io_gadget_header_def.h"
#include "io_gadget_def.h"
#include "io_logging.h"


/*--- Prototypes of exported functions ----------------------------------*/

/**
 * \brief Reads a Gadget header.
 *
 * The function will first rewind the file pointer to the start
 * of the header and then read in everything. Then it will
 * position the file pointer to the start of the particle date.
 *
 * \param log  A logging object.
 * \param f    A Gadget file object.
 *
 * \return A freshly filled header, or NULL, in case of memory
 *         problems.
 */
extern io_gadget_header_t
io_gadget_header_get(io_logging_t log, io_gadget_t f);


/**
 * \brief This will delete a gadget.header object.
 *
 * \param log      The logging object.
 * \param *header  A pointer to the variable holding the header object.
 *                 This variable will be set to NULL.
 *
 * \return Nothing.
 */
extern void
io_gadget_header_del(io_logging_t log, io_gadget_header_t *header);


/**
 * \brief Writes a header to the file.
 *
 * \param log     The logging object.
 * \param header  The header to write.
 * \param f       The file the header will be written to.
 *
 * \return Nothing.
 */
extern void
io_gadget_header_write(io_logging_t       log,
                       io_gadget_header_t header,
                       io_gadget_t        f);


/**
 * \briefs Writes the header information to the logfile.
 *
 * \param log     The logging object.
 * \param header  The header object.
 *
 * \return Nothing.
 */
extern void
io_gadget_header_log(io_logging_t log, io_gadget_header_t header);


#endif
