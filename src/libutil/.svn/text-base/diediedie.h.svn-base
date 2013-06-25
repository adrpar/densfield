#ifndef DIEDIEDIE_H
#define DIEDIEDIE_H

/**
 * \file  diediedie.h
 *
 *  Provides definitions for an abort function.
 */


/***********************************************************************\
 *    Global defines                                                   * 
\***********************************************************************/
/**
 * \brief  This is a generic panic-stop function, implemented as a macro
 *         to allow for function and line number information in the
 *         calling process.
 *
 * \param  a  The error code to return.
 *
 * \return  Never returns, instead aborts the program.
 */
#define diediedie(a) \
{\
	fprintf(stderr, \
	        "Something went horribly wrong in %s() at %s:%i\n"\
	        "Terminating with error code: %i\n\n", \
	        __func__, __FILE__, __LINE__, (a));\
	exit((a)); \
}


#endif /* DIEDIEDIE_H */
