/* ==================== *
 * <buffers.c>
 * Bailey Jia-Tao Brown
 * 2022
 *
 * Source file for buffer data and functions
 * Contents:
 *	- Includes
 *	- Internal data
 *	- Internal init and terminate functions
 *	- Buffer related functions
 * ==================== */

/* INCLUDES */
#include "internals.h"

/* INTERNAL DATA */
static viBufferBehavior* viBufferBehaviors; /* buffer behavior array */
static uint16_t viBufferBehaviorCount;      /* behavior counter      */

static viBuffer** viBuffers;     /* pointer to buffer objects */
static uint16_t   viBufferCount; /* buffer object counter     */
static uint8_t*   viBufferField; /* buffer use field          */

/* INTERNAL INIT AND TERMINATE FUNCTIONS */
VIAPI void __viBufferInit(void);
VIAPI void __viBufferTerminate(void);

/* BUFFER FUNCTIONS */
VIAPI viHandle viCreateBufferBehavior(char* name, uint32_t default,
	uint32_t step);
VIAPI viHandle viCreateBufferBehaviorC(viBufferBehavior reference);
VIAPI viHandle viCreateBuffer(viHandle behavior);
VIAPI void* viGetBufferIndex(viHandle buffer, uint64_t index);
VIAPI void viBufferAdd(viHandle buffer, void* data);
VIAPI void viBufferRemove(viHandle buffer, uint64_t index);