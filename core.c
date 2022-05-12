/* ==================== *
 * <core.c>
 * Bailey Jia-Tao Brown
 * 2022
 * 
 * Source file for init and terminate functions
 * Contents:
 *	- Includes
 *	- Init functions
 *	- Terminate function
 * ==================== */

/* INCLUDES */
#include "internals.h"

VIAPI void viInit(void)
{
	__viBufferInit( );
}

VIAPI void viTerminate(void)
{
	__viBufferTerminate();
}

