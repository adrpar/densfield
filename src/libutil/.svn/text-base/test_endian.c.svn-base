/**
 * \file  test_endian.c
 *
 *  Provides a function to test the endianess of the machine it is
 *  running on.
 */


/***********************************************************************
 *    Includes                                                         *
 ***********************************************************************/
#include "test_endian.h"


/***********************************************************************
 *    Implementation of exported functions                             * 
 ***********************************************************************/
extern int
test_endian(void)
{
	int test = 1;

	if ( ((char *)(&test))[0] == 1 )
		return 0;

	return 1;
}
